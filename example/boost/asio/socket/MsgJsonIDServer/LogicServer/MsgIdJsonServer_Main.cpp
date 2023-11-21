//
// Created by wz on 23-11-20.
//
#include <iostream>
#include "CServer.h"
#include "glog/logging.h"
using namespace std;
int main()
{
  try {
    boost::asio::io_context  io_context;
    CServer s(io_context, 10086);
    io_context.run();
  }
  catch (std::exception& e) {
    LOG(ERROR) << "Exception: " << e.what() << endl;
  }
  boost::asio::io_context io_context;
}