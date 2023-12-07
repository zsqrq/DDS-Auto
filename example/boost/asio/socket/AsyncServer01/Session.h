//
// Created by wz on 23-11-9.
//
#ifndef FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_ASYNCSERVER01_SESSION_H_
#define FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_ASYNCSERVER01_SESSION_H_
#include <iostream>
#include "boost/asio.hpp"

class Session {
 public:
  Session(boost::asio::io_context& io_context) : _socket(io_context) {}

  boost::asio::ip::tcp::socket& Socket() {
    return _socket;
  }

  void Start();

 private:
  void handle_read(const boost::system::error_code& error, size_t bytes_transfered);
  void handle_write(const boost::system::error_code& error);
  boost::asio::ip::tcp::socket _socket;
  enum {max_length = 1024};
  char _data[max_length];
};

class Server {
 public:
  Server(boost::asio::io_context& io_context, short port);

 private:
  void start_accept();
  void handle_accept(Session* new_session, const boost::system::error_code& error);
  boost::asio::io_context& _ioc;
  boost::asio::ip::tcp::acceptor _acceptor;
};

#endif //FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_ASYNCSERVER01_SESSION_H_
