//
// Created by wz on 23-11-23.
//
#include <iostream>
#include "CServer.h"
#include "SingleTon.h"
#include "LogicSystem.h"
#include <csignal>
#include <thread>
#include <mutex>
#include "AsioThreadPool.h"
#include "glog/logging.h"
using namespace std;

int main(int argc,char* argv[]) {
  FLAGS_minloglevel = 0;
  FLAGS_alsologtostderr = 1;
  google::InitGoogleLogging(argv[0]);
  try {
    auto pool = AsioThreadPool::GetInstance();
    boost::asio::io_context io_context;
    boost::asio::signal_set signals(io_context, SIGINT, SIGTERM);
    signals.async_wait([pool,&io_context](auto, auto) {
      io_context.stop();
      pool->Stop();
    });

    CServer s(pool->GetIOService(), 10086);

    io_context.run();
    LOG(INFO) << "server exited ....";
  }
  catch (std::exception& e) {
    LOG(ERROR) << "Exception: " << e.what();
  }
  return 0;
}
