//
// Created by wz on 23-11-21.
//

#ifndef FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_LOGICSERVER_LOGICSERVER01_MSGNODE_H_
#define FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_LOGICSERVER_LOGICSERVER01_MSGNODE_H_
#include <string>
#include <iostream>
#include "const.h"
#include "boost/asio.hpp"
#include "glog/logging.h"

using namespace std;
using boost::asio::ip::tcp;

class LogicSystem;

class MsgNode {
 public:
  MsgNode(short max_len) : _total_len(max_len), _cur_len(0) {
    _data = new char[_total_len + 1]();
    _data[_total_len] = '\0';
  }

  ~MsgNode(){
    LOG(INFO) << "Destruct MsgNode" ;
    delete[] _data;
  }

  void Clear() {
    std::memset(_data, 0, _total_len);
    _cur_len = 0;
  }

  short _cur_len;
  short _total_len;
  char* _data;
};
using MsgNodePtr = std::shared_ptr<MsgNode>;

class RecvNode : public MsgNode {
  friend class LogicSystem;
 public:
  RecvNode(short max_len, short msg_id);
 private:
  short _msg_id;
};
using RecvNodePtr = std::shared_ptr<RecvNode>;

class SendNode : public MsgNode {
  friend class LogicSystem;
 public:
  SendNode(const char* msg, short max_len, short msg_id);
 private:
  short _msg_id;
};

#endif  // FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_LOGICSERVER_LOGICSERVER01_MSGNODE_H_
