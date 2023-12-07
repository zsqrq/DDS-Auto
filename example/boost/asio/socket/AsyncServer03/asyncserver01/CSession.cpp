//
// Created by wz on 23-11-13.
//
#include "CSession.h"
#include "CServer.h"
#include "glog/logging.h"
#include <iostream>

CSession::CSession(boost::asio::io_context &io_context, CServer *server) :
    _socket(io_context),_server(server),_b_close(false),_b_head_parse(false){
  auto a_uuid = boost::uuids::random_generator()();
  _uuid = boost::uuids::to_string(a_uuid);
  _recv_head_node = std::make_shared<MsgNode>(HEAD_LENGTH);
}
CSession::~CSession() {
  LOG(INFO) << "~CSession destruct";
}

tcp::socket& CSession::GetSocket() {
  return _socket;
}

std::string& CSession::GetUuid() {
  return _uuid;
}

void CSession::Start() {
  ::memset(_data,0,MAX_LENGTH);
  _socket.async_read_some(boost::asio::buffer(_data,MAX_LENGTH),
                          std::bind(&CSession::HandleRead,this,
                                    std::placeholders::_1, std::placeholders::_2,SharedSelf()));
}

void CSession::HandleRead(const boost::system::error_code& error, size_t  bytes_transferred, std::shared_ptr<CSession> shared_self){
  if (!error) {
    int copy_len = 0;
    while (bytes_transferred>0) {
      if (!_b_head_parse) {
        if (bytes_transferred + _recv_head_node->_cur_len < HEAD_LENGTH) {
          memcpy(_recv_head_node->_data + _recv_head_node->_cur_len, _data+ copy_len, bytes_transferred);
          _recv_head_node->_cur_len += bytes_transferred;
          ::memset(_data, 0, MAX_LENGTH);
          _socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
                                  std::bind(&CSession::HandleRead, this, std::placeholders::_1, std::placeholders::_2, shared_self));
          return;
        }

        int head_remain = HEAD_LENGTH - _recv_head_node->_cur_len;
        memcpy(_recv_head_node->_data + _recv_head_node->_cur_len, _data+copy_len, head_remain);

        copy_len += head_remain;
        bytes_transferred -= head_remain;
        short data_len = 0;
        memcpy(&data_len, _recv_head_node->_data, HEAD_LENGTH);
        LOG(INFO) << "data_len is " << data_len;
        if (data_len > MAX_LENGTH) {
          LOG(INFO)<< "invalid data length is " << data_len;
          _server->ClearSession(_uuid);
          return;
        }
        _recv_msg_node = make_shared<MsgNode>(data_len);

        if (bytes_transferred < data_len) {
          memcpy(_recv_msg_node->_data + _recv_msg_node->_cur_len, _data + copy_len, bytes_transferred);
          _recv_msg_node->_cur_len += bytes_transferred;
          ::memset(_data, 0, MAX_LENGTH);
          _socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
                                  std::bind(&CSession::HandleRead, this,
                                            std::placeholders::_1, std::placeholders::_2, shared_self));
          _b_head_parse = true;
          return;
        }

        memcpy(_recv_msg_node->_data + _recv_msg_node->_cur_len, _data + copy_len, data_len);
        _recv_msg_node->_cur_len += data_len;
        copy_len += data_len;
        bytes_transferred -= data_len;
        _recv_msg_node->_data[_recv_msg_node->_total_len] = '\0';
        LOG(INFO) << "receive data is " << _recv_msg_node->_data << endl;

        Send(_recv_msg_node->_data, _recv_msg_node->_total_len);
        _b_head_parse = false;
        _recv_head_node->Clear();
        if (bytes_transferred <= 0) {
          ::memset(_data, 0, MAX_LENGTH);
          _socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
                                  std::bind(&CSession::HandleRead, this,
                                            std::placeholders::_1, std::placeholders::_2, shared_self));
          return;
        }
        continue;
      }

      int remain_msg = _recv_msg_node->_total_len - _recv_msg_node->_cur_len;
      if (bytes_transferred < remain_msg) {
        memcpy(_recv_msg_node->_data + _recv_msg_node->_cur_len, _data + copy_len, bytes_transferred);
        _recv_msg_node->_cur_len += bytes_transferred;
        ::memset(_data, 0, MAX_LENGTH);
        _socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
                                std::bind(&CSession::HandleRead, this,
                                          std::placeholders::_1, std::placeholders::_2, shared_self));
        return;
      }
      memcpy(_recv_msg_node->_data + _recv_msg_node->_cur_len, _data + copy_len, remain_msg);
      _recv_msg_node->_cur_len += remain_msg;
      bytes_transferred -= remain_msg;
      copy_len += remain_msg;
      _recv_msg_node->_data[_recv_msg_node->_total_len] = '\0';
      LOG(INFO) << "receive data is " << _recv_msg_node->_data;

      Send(_recv_msg_node->_data, _recv_msg_node->_total_len);
      _b_head_parse = false;
      _recv_head_node->Clear();
      if (bytes_transferred <= 0) {
        ::memset(_data, 0, MAX_LENGTH);
        _socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
                                std::bind(&CSession::HandleRead, this,
                                          std::placeholders::_1, std::placeholders::_2, shared_self));
        return;
      }
      continue;
    }
  }
  else {
    LOG(ERROR) << "handle read failed, error is " << error.what();
    Close();
    _server->ClearSession(_uuid);
  }
}

void CSession::Send(char *msg, int max_length) {
  bool pending = false;
  std::lock_guard<std::mutex> lock(_send_lock);
  if (_send_que.size() > 0) {
    pending = true;
  }
  _send_que.push(make_shared<MsgNode>(msg, max_length));
  if (pending) {
    return;
  }
  auto& msgnode = _send_que.front();
  boost::asio::async_write(_socket, boost::asio::buffer(msgnode->_data, msgnode->_total_len),
                           std::bind(&CSession::HandleWrite,
                                     this, std::placeholders::_1, SharedSelf()));
}

void CSession::HandleWrite(const boost::system::error_code &error, CSessionPtr shared_self) {
  if (!error) {
    std::lock_guard<std::mutex> lock(_send_lock);
    LOG(INFO) << "send data " << _send_que.front()->_data+HEAD_LENGTH;
    _send_que.pop();
    if (!_send_que.empty()) {
      auto &msgnode = _send_que.front();
      boost::asio::async_write(_socket, boost::asio::buffer(msgnode->_data, msgnode->_total_len),
                               std::bind(&CSession::HandleWrite,
                                         this, std::placeholders::_1, shared_self));
    }
  } else {
    LOG(ERROR) << "handle write failed, error is " << error.what();
    Close();
    _server->ClearSession(_uuid);
  }
}

void CSession::Close() {
  _socket.close();
  _b_close = true;
}

std::shared_ptr<CSession>CSession::SharedSelf() {
  return shared_from_this();
}
