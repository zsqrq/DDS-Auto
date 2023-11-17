#include "CSession.h"
#include "CServer.h"
#include <iostream>
#include "../Message/msg.pb.h"
#include "glog/logging.h"
#include <sstream>

CSession::CSession(boost::asio::io_context& io_context, CServer* server):
                                                                           _socket(io_context), _server(server), _b_close(false),_b_head_parse(false){
  boost::uuids::uuid  a_uuid = boost::uuids::random_generator()();
  _uuid = boost::uuids::to_string(a_uuid);
  _recv_head_node = make_shared<MsgNode>(HEAD_LENGTH);
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
  ::memset(_data, 0, MAX_LENGTH);
  _socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH), std::bind(&CSession::HandleRead, this,
                                                                            std::placeholders::_1, std::placeholders::_2, SharedSelf()));
}

void CSession::Send(std::string msg) {
  std::lock_guard<std::mutex> lock(_send_lock);
  int send_que_size = _send_que.size();
  if (send_que_size > MAX_SENDQUE) {
    LOG(INFO) << "session: " << _uuid << " send que fulled, size is " << MAX_SENDQUE;
    return;
  }

  _send_que.push(make_shared<MsgNode>(msg.c_str(), msg.length()));
  if (send_que_size > 0) {
    return;
  }
  auto& msgnode = _send_que.front();
  boost::asio::async_write(_socket, boost::asio::buffer(msgnode->_data, msgnode->_total_len),
                           std::bind(&CSession::HandleWrite, this,
                                     std::placeholders::_1, SharedSelf()));
}

void CSession::Send(char* msg, int max_length) {
  std::lock_guard<std::mutex> lock(_send_lock);
  int send_que_size = _send_que.size();
  if (send_que_size > MAX_SENDQUE) {
    LOG(INFO) << "session: " << _uuid << " send que fulled, size is " << MAX_SENDQUE;
    return;
  }

  _send_que.push(make_shared<MsgNode>(msg, max_length));
  if (send_que_size>0) {
    return;
  }
  auto& msgnode = _send_que.front();
  boost::asio::async_write(_socket, boost::asio::buffer(msgnode->_data, msgnode->_total_len),
                           std::bind(&CSession::HandleWrite, this, std::placeholders::_1, SharedSelf()));
}

void CSession::Close() {
  _socket.close();
  _b_close = true;
}

std::shared_ptr<CSession>CSession::SharedSelf() {
  return shared_from_this();
}

void CSession::HandleWrite(const boost::system::error_code& error, CSessionPtr shared_self) {

  try {
    if (!error) {
      std::lock_guard<std::mutex> lock(_send_lock);
      //cout << "send data " << _send_que.front()->_data+HEAD_LENGTH << endl;
      _send_que.pop();
      if (!_send_que.empty()) {
        auto& msgnode = _send_que.front();
        boost::asio::async_write(_socket, boost::asio::buffer(msgnode->_data, msgnode->_total_len),
                                 std::bind(&CSession::HandleWrite, this, std::placeholders::_1, shared_self));
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

void CSession::HandleRead(const boost::system::error_code& error, size_t  bytes_transferred, CSessionPtr shared_self){
  try {
    if (!error) {

      int copy_len = 0;
      while (bytes_transferred > 0) {
        if (!_b_head_parse) {

          if (bytes_transferred + _recv_head_node->_cur_len < HEAD_LENGTH) {
            memcpy(_recv_head_node->_data + _recv_head_node->_cur_len, _data + copy_len, bytes_transferred);
            _recv_head_node->_cur_len += bytes_transferred;
            ::memset(_data, 0, MAX_LENGTH);
            _socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
                                    std::bind(&CSession::HandleRead, this, std::placeholders::_1, std::placeholders::_2, shared_self));
            return;
          }

          int head_remain = HEAD_LENGTH - _recv_head_node->_cur_len;
          memcpy(_recv_head_node->_data + _recv_head_node->_cur_len, _data + copy_len, head_remain);

          copy_len += head_remain;
          bytes_transferred -= head_remain;

          short data_len = 0;
          memcpy(&data_len, _recv_head_node->_data, HEAD_LENGTH);

          data_len = boost::asio::detail::socket_ops::network_to_host_short(data_len);
          LOG(INFO) << "data_len is " << data_len;

          if (data_len > MAX_LENGTH) {
            LOG(WARNING) << "invalid data length is " << data_len;
            _server->ClearSession(_uuid);
            return;
          }
          _recv_msg_node = make_shared<MsgNode>(data_len);

          if (bytes_transferred < data_len) {
            memcpy(_recv_msg_node->_data + _recv_msg_node->_cur_len, _data + copy_len, bytes_transferred);
            _recv_msg_node->_cur_len += bytes_transferred;
            ::memset(_data, 0, MAX_LENGTH);
            _socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
                                    std::bind(&CSession::HandleRead, this, std::placeholders::_1, std::placeholders::_2, shared_self));
            _b_head_parse = true;
            return;
          }

          memcpy(_recv_msg_node->_data + _recv_msg_node->_cur_len, _data + copy_len, data_len);
          _recv_msg_node->_cur_len += data_len;
          copy_len += data_len;
          bytes_transferred -= data_len;
          _recv_msg_node->_data[_recv_msg_node->_total_len] = '\0';
          //cout << "receive data is " << _recv_msg_node->_data << endl;

          MsgData msgdata;
          std::string receive_data;
          msgdata.ParseFromString(std::string(_recv_msg_node->_data, _recv_msg_node->_total_len));
          LOG(INFO) << "recevie msg id  is " << msgdata.id() << " msg data is " << msgdata.data();
          std::string return_str = "server has received msg, msg data is " + msgdata.data();
          MsgData msgreturn;
          msgreturn.set_id(msgdata.id());
          msgreturn.set_data(return_str);
          std::string return_string;
          msgreturn.SerializeToString(&return_string);
          Send(return_string);

          _b_head_parse = false;
          _recv_head_node->Clear();
          if (bytes_transferred <= 0) {
            ::memset(_data, 0, MAX_LENGTH);
            _socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
                                    std::bind(&CSession::HandleRead, this, std::placeholders::_1, std::placeholders::_2, shared_self));
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
                                  std::bind(&CSession::HandleRead, this, std::placeholders::_1, std::placeholders::_2, shared_self));
          return;
        }
        memcpy(_recv_msg_node->_data + _recv_msg_node->_cur_len, _data + copy_len, remain_msg);
        _recv_msg_node->_cur_len += remain_msg;
        bytes_transferred -= remain_msg;
        copy_len += remain_msg;
        _recv_msg_node->_data[_recv_msg_node->_total_len] = '\0';
        //cout << "receive data is " << _recv_msg_node->_data << endl;

        MsgData msgdata;
        std::string receive_data;
        msgdata.ParseFromString(std::string(_recv_msg_node->_data, _recv_msg_node->_total_len));
        LOG(INFO) << "recevie msg id  is " << msgdata.id() << " msg data is " << msgdata.data();
        std::string return_str = "server has received msg, msg data is " + msgdata.data();
        MsgData msgreturn;
        msgreturn.set_id(msgdata.id());
        msgreturn.set_data(return_str);
        msgreturn.SerializeToString(&return_str);
        Send(return_str);

        _b_head_parse = false;
        _recv_head_node->Clear();
        if (bytes_transferred <= 0) {
          ::memset(_data, 0, MAX_LENGTH);
          _socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
                                  std::bind(&CSession::HandleRead, this, std::placeholders::_1, std::placeholders::_2, shared_self));
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
  catch (std::exception& e) {
    LOG(ERROR) << "Exception code is " << e.what();
  }
}
