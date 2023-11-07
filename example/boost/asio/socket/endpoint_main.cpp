//
// Created by wz on 23-11-7.
//
#include <iostream>
#include "endpoints.h"

int main()
{
  client_end_point();
  server_end_point();
  create_tcp_socket();
  create_acceptor_socket();
  return 0;
}