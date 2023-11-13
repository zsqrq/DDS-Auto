//
// Created by wz on 23-11-10.
//
#include "boost/container/vector.hpp"
#include "glog/logging.h"
#include "CServer.h"
#include <iostream>

int main(int argc, char* argv[]) {
  try {boost::asio::io_context io_context;
    CServer c_server(io_context, 10086);
    io_context.run();
  } catch (std::exception& e) {
    LOG(ERROR) << "Exception: " << e.what();
  }
}