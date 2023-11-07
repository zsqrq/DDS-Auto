//
// Created by wz on 23-11-7.
//

#include <iostream>
#include "connection.h"
#include "glog/logging.h"

int accept_new_connection( ) {
  // The size of the queue containing the pending connection requests.
  constexpr int BACKLOG_SIZE = 30;

  // Step 1. Here we assume that the server application has already obtained the protocol port number.
  unsigned short port_num = 3333;

  // Step 2. Creating a server endpoint.
  boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address_v4::any(), port_num);
  boost::asio::io_context io_context;

  try {
    // Step 3. Instantiating and opening an acceptor socket.
    boost::asio::ip::tcp::acceptor acceptor(io_context, endpoint.protocol());
    // Step 4. Binding the acceptor socket to the server endpoint.
    acceptor.bind(endpoint);

    // Step 5. Starting to listen for incoming connection
    acceptor.listen(BACKLOG_SIZE);

    // Step 6. Creating an active socket.
    boost::asio::ip::tcp::socket sock(io_context);

    // Step 7. Processing the next connection request and connecting the active socket to the client.
    acceptor.accept(sock);
  } catch (boost::system::system_error& e) {
    LOG(INFO) << "Error occured! Error code = " << e.code()
              << ". Message: " << e.what();
    return e.code().value();
  }
}

void use_buffer_str() {
  boost::asio::const_buffers_1 out_buf = boost::asio::buffer("Hello World");
}

void use_buffer_array() {
  constexpr size_t BUF_SIZE_BYTES = 20;
  auto buf = std::make_unique<char[]>(BUF_SIZE_BYTES);
  auto input_buf = boost::asio::buffer(static_cast<void*>(buf.get()), BUF_SIZE_BYTES);
}

void use_const_buffer() {
  std::string buf = "Hello World";
  boost::asio::const_buffer asio_buf(buf.c_str(), buf.length());
  std::vector<boost::asio::const_buffer> buffer_sequence;
  buffer_sequence.push_back(asio_buf);
}