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

void sig_handler(int sig) {
  if (sig == SIGINT || sig == SIGTERM) {
    std::unique_lock<std::mutex> lock_quit(mutex_quit);
    bstop = true;
    lock_quit.unlock();
    cond_quit.notify_one();
  }
}

int main(int argc, char* argv[]) {
  FLAGS_minloglevel = 0;
  FLAGS_alsologtostderr =1;
  google::InitGoogleLogging(argv[0]);

  try {
    boost::asio::io_context io_context;
    std::thread net_work_thread([&io_context] {
      CServer s(io_context,10086);
      io_context.run();
    });
    ::signal(SIGINT,sig_handler);
    while (!bstop) {
      std::unique_lock<std::mutex> lock_quit(mutex_quit);
      cond_quit.wait(lock_quit);
    }
    io_context.stop();
    net_work_thread.join();
  } catch (std::exception& e) {
    LOG(ERROR) << "Exception: " << e.what();
  }
  return 0;
}
