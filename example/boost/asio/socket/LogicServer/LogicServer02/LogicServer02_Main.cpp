//
// Created by wz on 23-11-21.
//
#include <iostream>
#include <csignal>
#include <thread>
#include <mutex>

#include "CServer.h"
#include "CSession.h"
#include "LogicSystem.h"
#include "glog/logging.h"

using namespace std;
bool bstop = false;
std::condition_variable cond_quit;
std::mutex mutex_quit;


int main(int argc, char* argv[]) {
  FLAGS_minloglevel = 0;
  FLAGS_alsologtostderr =1;
  google::InitGoogleLogging(argv[0]);

  try {
    boost::asio::io_context io_context;
    boost::asio::signal_set signals(io_context,SIGINT,SIGTERM);
    signals.async_wait([&io_context](auto,auto ) {
      io_context.stop();
    });
    CServer s(io_context,10086);
    io_context.run();
  } catch (std::exception& e) {
    LOG(ERROR) << "Exception: " << e.what();
  }
  return 0;
}
