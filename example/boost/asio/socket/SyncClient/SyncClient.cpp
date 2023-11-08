//
// Created by wz on 23-11-8.
//
#include <iostream>
#include <memory>

#include "boost/asio.hpp"
#include "glog/logging.h"

constexpr int MAX_LENGTH = 1024;

using namespace boost;

int main(int argc, char* argv[]) {
  try {
    asio::io_context io_context;

    asio::ip::tcp::endpoint remote_ep(asio::ip::address::from_string("127.0.0.1"), 10086);
    asio::ip::tcp::socket sock(io_context);
    boost::system::error_code error1 = boost::asio::error::host_not_found;
    sock.connect(remote_ep,error1);

    if (error1) {
      LOG(ERROR) << "connect failed, code is " << error1.value() << " error msg is " << error1.message();
      return 0;
    }
    LOG(INFO) << "Enter message: ";
    char request[MAX_LENGTH];
    std::cin.getline(request, MAX_LENGTH);

    std::size_t request_length = strlen(request);
    boost::asio::write(sock, boost::asio::buffer(request,request_length));

    char reply[MAX_LENGTH];
    size_t reply_length = boost::asio::read(sock, boost::asio::buffer(reply,request_length));
    LOG(INFO) << "Reply is : ";
    LOG(INFO) << reply;
//    std::cout.write(reply, reply_length);
    io_context.run();
  } catch (std::exception& e) {
    LOG(ERROR) << "Exception: " << e.what();
  }
  return 0;
}