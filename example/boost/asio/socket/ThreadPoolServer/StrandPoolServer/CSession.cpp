//
// Created by wz on 23-11-23.
//

#include "CSession.h"
#include "CServer.h"
#include <iostream>
#include <sstream>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include "LogicSystem.h"
#include "glog/logging.h"

CSession::CSession(boost::asio::io_context& io_context, CServer* server):
    _socket(io_context), _server(server), _b_close(false),
    _b_head_parse(false), _strand(io_context.get_executor()){
  boost::uuids::uuid  a_uuid = boost::uuids::random_generator()();
  _uuid = boost::uuids::to_string(a_uuid);
  _recv_head_node = make_shared<MsgNode>(HEAD_TOTAL_LEN);
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

void CSession::Start(){
  std::memset(_data, 0, MAX_LENGTH);

  _socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
                          boost::asio::bind_executor(_strand, std::bind(&CSession::HandleRead, this,
                                                                        std::placeholders::_1, std::placeholders::_2, SharedSelf())));
}


void CSession::Send(std::string msg, short msgid) {
  std::lock_guard<std::mutex> lock(_send_lock);
  int send_que_size = _send_que.size();
  if (send_que_size > MAX_SENDQUE) {
    LOG(INFO) << "session: " << _uuid << " send que fulled, size is " << MAX_SENDQUE;
    return;
  }

  _send_que.push(make_shared<SendNode>(msg.c_str(), msg.length(), msgid));
  if (send_que_size > 0) {
    return;
  }
  auto& msgnode = _send_que.front();
  boost::asio::async_write(_socket, boost::asio::buffer(msgnode->_data, msgnode->_total_len),
                           boost::asio::bind_executor(_strand,std::bind(&CSession::HandleWrite, this,
                                                                        std::placeholders::_1, SharedSelf()))
  );
}

void CSession::Send(char* msg, short max_length, short msgid) {
  std::lock_guard<std::mutex> lock(_send_lock);
  int send_que_size = _send_que.size();
  if (send_que_size > MAX_SENDQUE) {
    LOG(INFO) << "session: " << _uuid << " send que fulled, size is " << MAX_SENDQUE;
    return;
  }

  _send_que.push(make_shared<SendNode>(msg, max_length, msgid));
  if (send_que_size>0) {
    return;
  }
  auto& msgnode = _send_que.front();
  boost::asio::async_write(_socket, boost::asio::buffer(msgnode->_data, msgnode->_total_len),
                           boost::asio::bind_executor(_strand, std::bind(&CSession::HandleWrite,
                                                                         this, std::placeholders::_1, SharedSelf()))
  );
}

void CSession::Close() {
  _socket.close();
  _b_close = true;
}

std::shared_ptr<CSession> CSession::SharedSelf() {
  return shared_from_this();
}

void CSession::HandleWrite(const boost::system::error_code& error, std::shared_ptr<CSession> shared_self) {
  try {
    if (!error) {
      std::lock_guard<std::mutex> lock(_send_lock);
      //cout << "send data " << _send_que.front()->_data+HEAD_LENGTH << endl;
      _send_que.pop();
      if (!_send_que.empty()) {
        auto& msgnode = _send_que.front();
        boost::asio::async_write(_socket, boost::asio::buffer(msgnode->_data, msgnode->_total_len),
                                 boost::asio::bind_executor(_strand, std::bind(&CSession::HandleWrite, this, std::placeholders::_1, shared_self))
        );
      }
    }
    else {
      LOG(ERROR) << "handle write failed, error is " << error.what();
      Close();
      _server->ClearSession(_uuid);
    }
  }
  catch (std::exception& e) {
    LOG(ERROR) << "Exception code : " << e.what();
  }
}

void CSession::HandleRead(const boost::system::error_code& error, size_t  bytes_transferred, std::shared_ptr<CSession> shared_self){
  try {
    if (!error) {
      int copy_len = 0;
      while (bytes_transferred > 0) {
        if (!_b_head_parse) {
          if (bytes_transferred + _recv_head_node->_cur_len < HEAD_TOTAL_LEN) {
            memcpy(_recv_head_node->_data + _recv_head_node->_cur_len, _data + copy_len, bytes_transferred);
            _recv_head_node->_cur_len += bytes_transferred;
            ::memset(_data, 0, MAX_LENGTH);
            _socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
                                    boost::asio::bind_executor(_strand,
                                                               std::bind(&CSession::HandleRead, this,
                                                                         std::placeholders::_1, std::placeholders::_2, shared_self))
            );
            return;
          }
          int head_remain = HEAD_TOTAL_LEN - _recv_head_node->_cur_len;
          memcpy(_recv_head_node->_data + _recv_head_node->_cur_len, _data + copy_len, head_remain);

          copy_len += head_remain;
          bytes_transferred -= head_remain;
          short msg_id = 0;
          memcpy(&msg_id, _recv_head_node->_data, HEAD_ID_LEN);
          msg_id = boost::asio::detail::socket_ops::network_to_host_short(msg_id);
          LOG(INFO) << "msg_id is " << msg_id;
          if (msg_id > MAX_LENGTH) {
            LOG(INFO) << "invalid msg_id is " << msg_id;
            _server->ClearSession(_uuid);
            return;
          }
          short msg_len = 0;
          memcpy(&msg_len, _recv_head_node->_data+HEAD_ID_LEN, HEAD_DATA_LEN);
          msg_len = boost::asio::detail::socket_ops::network_to_host_short(msg_len);
          LOG(INFO) << "msg_len is " << msg_len;
          if (msg_len > MAX_LENGTH) {
            LOG(INFO) << "invalid data length is " << msg_len;
            _server->ClearSession(_uuid);
            return;
          }

          _recv_msg_node = make_shared<RecvNode>(msg_len, msg_id);

          if (bytes_transferred < msg_len) {
            memcpy(_recv_msg_node->_data + _recv_msg_node->_cur_len, _data + copy_len, bytes_transferred);
            _recv_msg_node->_cur_len += bytes_transferred;
            ::memset(_data, 0, MAX_LENGTH);
            _socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
                                    boost::asio::bind_executor(_strand, std::bind(&CSession::HandleRead,
                                                                                  this, std::placeholders::_1, std::placeholders::_2, shared_self))
            );
            _b_head_parse = true;
            return;
          }

          memcpy(_recv_msg_node->_data + _recv_msg_node->_cur_len, _data + copy_len, msg_len);
          _recv_msg_node->_cur_len += msg_len;
          copy_len += msg_len;
          bytes_transferred -= msg_len;
          _recv_msg_node->_data[_recv_msg_node->_total_len] = '\0';
          LOG(INFO) << "receive data is " << _recv_msg_node->_data;
          LogicSystem::GetInstance()->PostMsgToQue(make_shared<LogicNode>(shared_from_this(), _recv_msg_node));

          _b_head_parse = false;
          _recv_head_node->Clear();
          if (bytes_transferred <= 0) {
            ::memset(_data, 0, MAX_LENGTH);
            _socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
                                    boost::asio::bind_executor(_strand, std::bind(&CSession::HandleRead, this,
                                                                                  std::placeholders::_1, std::placeholders::_2, shared_self))
            );
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
                                  boost::asio::bind_executor(_strand, std::bind(&CSession::HandleRead,
                                                                                this, std::placeholders::_1, std::placeholders::_2, shared_self))
          );
          return;
        }
        memcpy(_recv_msg_node->_data + _recv_msg_node->_cur_len, _data + copy_len, remain_msg);
        _recv_msg_node->_cur_len += remain_msg;
        bytes_transferred -= remain_msg;
        copy_len += remain_msg;
        _recv_msg_node->_data[_recv_msg_node->_total_len] = '\0';
        //cout << "receive data is " << _recv_msg_node->_data << endl;

        LogicSystem::GetInstance()->PostMsgToQue(make_shared<LogicNode>(shared_from_this(), _recv_msg_node));

        _b_head_parse = false;
        _recv_head_node->Clear();
        if (bytes_transferred <= 0) {
          ::memset(_data, 0, MAX_LENGTH);
          _socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
                                  boost::asio::bind_executor(_strand, std::bind(&CSession::HandleRead,
                                                                                this, std::placeholders::_1, std::placeholders::_2, shared_self))
          );
          return;
        }
        continue;
      }
    }
    else {
      LOG(INFO) << "handle read failed, error is " << error.what();
      Close();
      _server->ClearSession(_uuid);
    }
  }
  catch (std::exception& e) {
    LOG(INFO) << "Exception code is " << e.what();
  }
}

LogicNode::LogicNode(shared_ptr<CSession>  session,
                     shared_ptr<RecvNode> recvnode):_session(session),_recvnode(recvnode) {
}