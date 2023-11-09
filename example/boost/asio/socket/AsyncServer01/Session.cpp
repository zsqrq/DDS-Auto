//
// Created by wz on 23-11-9.
//
#include <iostream>

#include "Session.h"
#include "glog/logging.h"

void Session::Start() {
  memset(_data,0,max_length);
  _socket.async_read_some(boost::asio::buffer(_data,max_length),
                          std::bind(&Session::handle_read, this,
                                    std::placeholders::_1, std::placeholders::_2));
}

void Session::handle_read(const boost::system::error_code &error, size_t bytes_transfered) {
  if (!error) {
    LOG(ERROR) <<"server receive data is " << _data;
    boost::asio::async_write(_socket, boost::asio::buffer(_data, bytes_transfered),
                             std::bind(&Session::handle_write, this, std::placeholders::_1));
  } else {
    delete this;
  }
}