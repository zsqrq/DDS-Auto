//
// Created by wz on 23-11-20.
//

#ifndef FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_MSGJSONIDSERVER_LOGICSERVER_MSGNODE_H_
#define FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_MSGJSONIDSERVER_LOGICSERVER_MSGNODE_H_
#include <string>
#include <iostream>
#include <memory>
#include "boost/asio.hpp"
#include "Const.h"
#include "glog/logging.h"

using namespace std;
using boost::asio::ip::tcp;

class MsgNode {
 public:

  MsgNode(short max_len) : _total_len(max_len), _cur_len(0) {
    _data = new char[_total_len + 1]();
    _data[_total_len] = '\0';
  }

  ~MsgNode() {
    LOG(INFO) << "destruct MsgNode";
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

class RecvNode : public MsgNode {
 public:
  RecvNode(short max_len, short msg_id) ;

 private:
  short _msg_id;
};

class SendNode : public MsgNode {
 public:
  SendNode(const char* msg, short max_len, short msg_id);
 private:
  short _msg_id;
};

using MsgNodePtr = std::shared_ptr<MsgNode>;
using RecvNodePtr = std::shared_ptr<RecvNode>;
using SendNodePtr = std::shared_ptr<SendNode>;

#endif  // FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_MSGJSONIDSERVER_LOGICSERVER_MSGNODE_H_
