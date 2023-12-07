//
// Created by wz on 23-11-7.
//

#ifndef FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_IOOPERATION_CONNECTION_H_
#define FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_IOOPERATION_CONNECTION_H_
#include "boost/asio.hpp"

extern int accept_new_connection();
extern void use_buffer_str();
extern void use_buffer_array();
extern void use_const_buffer();
extern void use_stream_buffer();
extern int send_data_by_write_some();
extern int send_data_by_send();
extern int send_data_by_wirte();
extern int read_data_by_read_some();
extern int read_data_by_receive();
extern int read_data_by_read();
extern std::string read_data_by_until(boost::asio::ip::tcp::socket& sock);
extern int async_write_data();

#endif //FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_IOOPERATION_CONNECTION_H_
