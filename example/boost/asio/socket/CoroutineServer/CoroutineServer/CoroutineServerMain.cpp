//
// Created by wz on 23-11-24.
//
#include <iostream>
#include "CServer.h"
#include "LogicSystem.h"
#include <csignal>
#include <thread>
#include <mutex>
#include "AsioServicePool.h"
#include "glog/logging.h"
using namespace std;
bool bstop = false;
std::condition_variable cond_quit;
std::mutex mutex_quit;

int main(int argc, char * argv[])
{
  FLAGS_minloglevel = 0;
  FLAGS_alsologtostderr =1;
  google::InitGoogleLogging(argv[0]);
  try {
    auto &pool = AsioIOServicePool::GetInstance();
    boost::asio::io_context  io_context;
    boost::asio::signal_set signals(io_context, SIGINT, SIGTERM);
    signals.async_wait([&io_context, &pool](auto, auto) {
      io_context.stop();
      pool.Stop();
    });
    CServer s(io_context, 10086);
    io_context.run();
  }
  catch (std::exception& e) {
    LOG(ERROR) << "Exception: " << e.what() ;
  }

}
