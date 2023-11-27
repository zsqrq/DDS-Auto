//
// Created by wz on 23-11-24.
//

#include "CSession.h"
#include <json/json.h>
#include <json/reader.h>
#include <json/value.h>
#include <iostream>
#include <sstream>
#include "CServer.h"
#include "LogicSystem.h"
#include "glog/logging.h"

#if defined(BOOST_ASIO_ENABLE_HANDLER_TRACKING)
#define use_awaitable \
  boost::asio::use_awaitable_t(__FILE__, __LINE__, __PRETTY_FUNCTION__)
#endif

CSession::CSession(boost::asio::io_context& io_context, CServer* server)
    : _io_context(io_context),
      _socket(io_context),
      _server(server),
      _b_close(false),
      _b_head_parse(false) {
  boost::uuids::uuid a_uuid = boost::uuids::random_generator()();
  _uuid = boost::uuids::to_string(a_uuid);
  _recv_head_node = make_shared<MsgNode>(HEAD_TOTAL_LEN);
}

CSession::~CSession() {
  try {
    LOG(INFO) << "~CSession destruct";
    Close();
    // std::this_thread::sleep_for(std::chrono::seconds(1));
  } catch (std::exception& exp) {
    LOG(ERROR) << "exception is " << exp.what();
  }
}

tcp::socket& CSession::GetSocket() { return _socket; }

std::string& CSession::GetUuid() { return _uuid; }

void CSession::Start() {
  auto shared_this = shared_from_this();
  co_spawn(
      _io_context,
      [=]() -> awaitable<void> {
        try {
          for (; !_b_close;) {
            _recv_head_node->Clear();
            std::size_t n = co_await boost::asio::async_read(
                _socket,
                boost::asio::buffer(_recv_head_node->_data, HEAD_TOTAL_LEN),
                use_awaitable);
            if (n == 0) {
              LOG(INFO) << "receive peer closed";
              Close();
              _server->ClearSession(_uuid);
              co_return;
            }
            short msg_id = 0;
            memcpy(&msg_id, _recv_head_node->_data, HEAD_ID_LEN);
            msg_id =
                boost::asio::detail::socket_ops::network_to_host_short(msg_id);
            LOG(INFO) << "msg_id is " << msg_id;
            if (msg_id > MAX_LENGTH) {
              LOG(INFO) << "invalid msg_id is " << msg_id;
              _server->ClearSession(_uuid);
              co_return;
            }
            short msg_len = 0;
            memcpy(&msg_len, _recv_head_node->_data + HEAD_ID_LEN,
                   HEAD_DATA_LEN);
            msg_len =
                boost::asio::detail::socket_ops::network_to_host_short(msg_len);
            LOG(INFO) << "msg_len is " << msg_len;
            if (msg_len > MAX_LENGTH) {
              LOG(INFO) << "invalid data length is " << msg_len;
              _server->ClearSession(_uuid);
              co_return;
            }
            _recv_msg_node = make_shared<RecvNode>(msg_len, msg_id);
            n = co_await boost::asio::async_read(
                _socket,
                boost::asio::buffer(_recv_msg_node->_data,
                                    _recv_msg_node->_total_len),
                use_awaitable);
            if (n == 0) {
              LOG(INFO) << "receive peer closed";
              Close();
              _server->ClearSession(_uuid);
              co_return;
            }
            _recv_msg_node->_data[_recv_msg_node->_total_len] = '\0';
            LOG(INFO) << "receive data is " << _recv_msg_node->_data;
            LogicSystem::GetInstance().PostMsgToQue(
                make_shared<LogicNode>(shared_from_this(), _recv_msg_node));
          }
        } catch (std::exception& e) {
          LOG(INFO) << "exception is " << e.what();
          Close();
          _server->ClearSession(_uuid);
        }
      },
      detached);
}

void CSession::Send(std::string msg, short msgid) {
  Send(msg.c_str(), msg.length(), msgid);
}

void CSession::Send(const char* msg, short max_length, short msgid) {
  std::unique_lock<std::mutex> lock(_send_lock);
  int send_que_size = _send_que.size();
  if (send_que_size > MAX_SENDQUE) {
    LOG(INFO) << "session: " << _uuid << " send que fulled, size is "
              << MAX_SENDQUE;
    return;
  }

  _send_que.push(make_shared<SendNode>(msg, max_length, msgid));
  if (send_que_size > 0) {
    return;
  }
  auto msgnode = _send_que.front();
  lock.unlock();
  boost::asio::async_write(
      _socket, boost::asio::buffer(msgnode->_data, msgnode->_total_len),
      std::bind(&CSession::HandleWrite, this, std::placeholders::_1,
                SharedSelf()));
}

void CSession::Close() {
  _socket.close();
  _b_close = true;
}

std::shared_ptr<CSession> CSession::SharedSelf() { return shared_from_this(); }

void CSession::HandleWrite(const boost::system::error_code& error,
                           std::shared_ptr<CSession> shared_self) {
  try {
    if (!error) {
      std::unique_lock<std::mutex> lock(_send_lock);
      // cout << "send data " << _send_que.front()->_data+HEAD_LENGTH << endl;
      _send_que.pop();
      if (!_send_que.empty()) {
        auto msgnode = _send_que.front();
        lock.unlock();
        boost::asio::async_write(
            _socket, boost::asio::buffer(msgnode->_data, msgnode->_total_len),
            std::bind(&CSession::HandleWrite, this, std::placeholders::_1,
                      shared_self));
      }
    } else {
      LOG(INFO) << "handle write failed, error is " << error.what();
      Close();
      _server->ClearSession(_uuid);
    }
  } catch (std::exception& e) {
    LOG(ERROR) << "Exception code : " << e.what();
    Close();
    _server->ClearSession(_uuid);
  }
}

LogicNode::LogicNode(shared_ptr<CSession> session,
                     shared_ptr<RecvNode> recvnode)
    : _session(session), _recvnode(recvnode) {}