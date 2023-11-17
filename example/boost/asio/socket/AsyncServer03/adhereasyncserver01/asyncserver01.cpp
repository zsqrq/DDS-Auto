//
// Created by wz on 23-11-13.
//
#include <iostream>
#include "CServer.h"
#include "glog/logging.h"

int main(int arhc, char* argv[]) {
  FLAGS_logtostderr = 1;  // 设置日志输出到stderr，而不是文件
  FLAGS_minloglevel = 0;  // 设置最低日志级别为INFO
  google::InitGoogleLogging("Async Server");
  try {
    boost::asio::io_context io_context;
    CServer s(io_context, 10086);
    io_context.run();
  } catch (std::exception& e) {
    LOG(ERROR) << "Exception: " << e.what();
//    boost::asio::io_context io_context;
  }
}
