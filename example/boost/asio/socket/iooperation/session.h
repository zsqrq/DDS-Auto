//
// Created by wz on 23-11-8.
//

#ifndef FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_IOOPERATION_SESSION_H_
#define FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_IOOPERATION_SESSION_H_
#include <iostream>
#include <queue>
#include <memory>

#include "boost/asio.hpp"

constexpr int RECVSIZE = 1024;

class MsgNode{
 public:
  MsgNode(const char * msg, int total_len)
  : total_len_(total_len), cur_len_(0) {
    msg_ = new char[total_len];
    memmove(msg_, msg, total_len);
  }
  MsgNode(int total_len) :total_len_(total_len), cur_len_(0) {
    msg_ = new char[total_len];
  }
  ~MsgNode(){
    delete[] msg_;
  }

  char* msg_;
  int total_len_;
  int cur_len_;
};
using MsgNodePtr = std::shared_ptr<MsgNode>;
class Session{
 public:
  Session(std::shared_ptr<boost::asio::ip::tcp::socket> socket);
  void Connect(const boost::asio::ip::tcp::endpoint& ep);
  void WriteCallBack(const boost::system::error_code& ec, std::size_t bytes_transferred);
  void WriteToSocket(const std::string &buf);
  void WriteAllToSocket(const std::string& buf);
  void WriteAllCallBack(const boost::system::error_code& ec, std::size_t bytes_transferred);
  void ReadFromSocket();
  void ReadCallBack(const boost::system::error_code& ec, std::size_t bytes_transferred);
  void ReadAllFromSocket(const std::string& buf);
  void ReadAllCallBack(const boost::system::error_code& ec, std::size_t bytes_transferred);
  void WriteCallBackErr(const boost::system::error_code& ec, std::size_t bytes_transferred, MsgNodePtr);
  void WriteToSocketErr(const std::string& buf);

 private:
  std::queue<std::shared_ptr<MsgNode>> _send_queue;
  std::shared_ptr<boost::asio::ip::tcp::socket> _socket;
  std::shared_ptr<MsgNode> _recv_node;
  std::shared_ptr<MsgNode> _send_node;
  bool _send_pending;
  bool _recv_pending;
};

#endif //FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_IOOPERATION_SESSION_H_
