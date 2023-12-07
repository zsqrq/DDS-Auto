//
// Created by wz on 23-11-10.
//
#include <iostream>

#include "boost/asio.hpp"
#include "glog/logging.h"
#include "Session.h"

int main(int argc, char* argv[]) {
  FLAGS_logtostderr = 1;  // 设置日志输出到stderr，而不是文件
  FLAGS_minloglevel = 0;  // 设置最低日志级别为INFO
  google::InitGoogleLogging("Async Server");
  try {
    boost::asio::io_context io_context;
    Server s(io_context, 10086);
    io_context.run();
  } catch (std::exception& e) {
    LOG(ERROR) << "Exception: " << e.what();
  }
  return 0;
}
