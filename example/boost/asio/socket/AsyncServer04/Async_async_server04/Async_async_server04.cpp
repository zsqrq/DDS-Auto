//
// Created by wz on 23-11-15.
//
#include <iostream>
#include "CServer.h"
#include "CSession.h"
#include "glog/logging.h"

int main(int argc, char* argv[]) {
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging("Server");

  try {
    boost::asio::io_context io_context;
    CServer server(io_context,10086);
    io_context.run();
  } catch (std::exception& e) {
    LOG(ERROR) << "Exception: " << e.what();
  }
  boost::asio::io_context io_context;
  return 0;
}