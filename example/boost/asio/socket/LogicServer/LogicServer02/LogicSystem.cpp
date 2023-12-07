//
// Created by wz on 23-11-21.
//

#include "LogicSystem.h"

using namespace std;

LogicSystem::LogicSystem():_b_stop(false) {
  RegisterCallBacks();
  _worker_thread = std::thread(&LogicSystem::DealMsg, this);
}

LogicSystem::~LogicSystem() {
  _b_stop = true;
  _consume.notify_one();
  _worker_thread.join();
}

void LogicSystem::PostMsgToQue(std::shared_ptr<LogicNode> msg) {
  std::unique_lock<std::mutex> unique_lock(_mutex);
  _msg_que.push(msg);
  if (_msg_que.size() == 1) {
    unique_lock.unlock();
    _consume.notify_one();
  }
}

void LogicSystem::DealMsg() {
  for (;;) {
    std::unique_lock<std::mutex> unique_lock(_mutex);
    while (_msg_que.empty() && !_b_stop) {
      _consume.wait(unique_lock);
    }
    if (_b_stop ) {
      while (!_msg_que.empty()) {
        auto msg_node = _msg_que.front();
        LOG(INFO) << "recv_msg id  is " << msg_node->_recvnode->_msg_id;
        auto call_back_iter = _fun_callbacks.find(msg_node->_recvnode->_msg_id);
        if (call_back_iter == _fun_callbacks.end()) {
          _msg_que.pop();
          continue;
        }
        call_back_iter->second(msg_node->_session, msg_node->_recvnode->_msg_id,
                               std::string(msg_node->_recvnode->_data, msg_node->_recvnode->_cur_len));
        _msg_que.pop();
      }
      break;
    }
    auto msg_node = _msg_que.front();
    LOG(INFO) << "recv_msg id  is " << msg_node->_recvnode->_msg_id;
    auto call_back_iter = _fun_callbacks.find(msg_node->_recvnode->_msg_id);
    if (call_back_iter == _fun_callbacks.end()) {
      _msg_que.pop();
      continue;
    }
    call_back_iter->second(msg_node->_session, msg_node->_recvnode->_msg_id,
                           std::string(msg_node->_recvnode->_data, msg_node->_recvnode->_cur_len));
    _msg_que.pop();
  }
}

void LogicSystem::RegisterCallBacks() {
  _fun_callbacks[MSG_HELLO_WORD] =std::bind(&LogicSystem::HelloWorldCallBack,this,
                                             std::placeholders::_1,std::placeholders::_2, std::placeholders::_3);
}

void LogicSystem::HelloWorldCallBack(CSessionPtr session, short msg_id, std::string msg_data) {
  Json::Reader reader;
  Json::Value root;
  reader.parse(msg_data,root);
  LOG(INFO) << "recevie msg id  is " << root["id"].asInt() << " msg data is "
            << root["data"].asString();
  root["data"] ="server has received msg, msg data is " + root["data"].asString();
  std::string return_str = root.toStyledString();
  session->Send(return_str,root["id"].asInt());
}