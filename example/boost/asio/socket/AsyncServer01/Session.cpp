//
// Created by wz on 23-11-9.
//
#include "Session.h"

#include <iostream>

#include "glog/logging.h"

void Session::Start() {
  memset(_data, 0, max_length);
  _socket.async_read_some(
      boost::asio::buffer(_data, max_length),
      std::bind(&Session::handle_read, this, std::placeholders::_1,
                std::placeholders::_2));
}

void Session::handle_read(const boost::system::error_code &error,
                          size_t bytes_transfered) {
  if (!error) {
    LOG(INFO) << "server receive data is " << _data;
    boost::asio::async_write(
        _socket, boost::asio::buffer(_data, bytes_transfered),
        std::bind(&Session::handle_write, this, std::placeholders::_1));
  } else {
    delete this;
  }
}

void Session::handle_write(const boost::system::error_code &error) {
  if (!error) {
    memset(_data, 0, max_length);
    _socket.async_read_some(
        boost::asio::buffer(_data, max_length),
        std::bind(&Session::handle_read, this, std::placeholders::_1,
                  std::placeholders::_2));
  } else {
    delete this;
  }
}

Server::Server(boost::asio::io_context &io_context, short port)
    : _ioc(io_context),
      _acceptor(io_context, boost::asio::ip::tcp::endpoint(
                                boost::asio::ip::tcp::v4(), port)) {
  start_accept();
}

void Server::start_accept() {
  Session *new_session = new Session(_ioc);
  _acceptor.async_accept(new_session->Socket(),
                         std::bind(&Server::handle_accept, this, new_session,
                                   std::placeholders::_1));
}

void Server::handle_accept(Session *new_session,
                           const boost::system::error_code &error) {
  if (!error) {
    new_session->Start();
  } else {
    delete new_session;
  }
  start_accept();
}