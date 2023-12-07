//
// Created by wz on 23-11-16.
//
#include <iostream>

#include "glog/logging.h"
#include "CServer.h"

int main(int argc, char** argv) {
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging("Protobuf AsyncServer");

  try {
    boost::asio::io_context io_context;
    CServer server(io_context,10086);
    io_context.run();
  } catch (std::exception& e) {
    LOG(ERROR) << "Exception: " << e.what();
  }
}
