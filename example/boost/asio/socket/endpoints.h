//
// Created by wz on 23-11-7.
//

#ifndef FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_ENDPOINTS_H_
#define FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_ENDPOINTS_H_

#include "boost/asio.hpp"
#include <iostream>

extern  int  client_end_point();
extern  int  server_end_point();
extern  int  create_tcp_socket();
extern  int  create_acceptor_socket();
extern  int  bind_acceptor_socket();
extern  int  connect_to_end();
extern  int dns_connect_to_end();

#endif //FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_ENDPOINTS_H_
