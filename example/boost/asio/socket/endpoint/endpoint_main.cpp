//
// Created by wz on 23-11-7.
//
#include <iostream>
#include "endpoints.h"
#include "glog/logging.h"

int main(int argc, char* argv[])
{
  google::InitGoogleLogging(argv[0]);
  client_end_point();
  server_end_point();
  create_tcp_socket();
  create_acceptor_socket();
  return 0;
}