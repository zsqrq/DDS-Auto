//
// Created by wz on 23-11-8.
//

#ifndef FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_IOOPERATION_SESSION_H_
#define FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_IOOPERATION_SESSION_H_
#include <iostream>
#include <queue>
#include "boost/asio.hpp"

constexpr int RECVSIZE = 1024;

class MsgNode{};

class Session{
 public:
  Session(std::shared_ptr<boost::asio::ip::tcp::socket> socket){}
};

#endif //FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_IOOPERATION_SESSION_H_
