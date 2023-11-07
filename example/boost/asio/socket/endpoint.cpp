//
// Created by wz on 23-11-7.
//
#include <iostream>
#include "endpoints.h"

int client_end_point() {
  // Step 1.
  std::string raw_ip_address = "127.0.0.1";
  unsigned short port_num = 3333;
  boost::system::error_code ec;

  // Step 2.
  boost::asio::ip::address ip_address = boost::asio::ip::address::from_string(raw_ip_address,ec);

  if (ec.value() != 0) {
    std::cout << "Failed to parse the IP address. Error code = "
              << ec.value() << "Message is :" << ec.message() << std::endl;
    return ec.value();
  }

  // Step 3.
  boost::asio::ip::tcp::endpoint ep(ip_address, port_num);
  // Step 4.
  return 0;
}

int server_end_point() {
  // Step 1.
  unsigned short port_num = 3333;

  // Step 2.
  boost::asio::ip::address ip_address = boost::asio::ip::address_v6::any();

  // Step 3.
  boost::asio::ip::tcp::endpoint ep(ip_address, port_num);

  // Step 4.
  return 0;
}

int create_tcp_socket() {
  // Step 1.
  boost::asio::io_context io_context;

  // Step 2.
  boost::asio::ip::tcp protocl = boost::asio::ip::tcp::v4();

  // Step 3.
  boost::asio::ip::tcp::socket sock(io_context);
  boost::system::error_code ec;

  // Step 4.
  sock.open(protocl, ec);
  if (ec.value() != 0) {
    // Failed to open the socket.
    std::cout
        << "Failed to open the socket! Error code = "
        << ec.value() << ". Message: " << ec.message();
    return ec.value();
  }

  return 0;
}

int create_acceptor_socket() {
  // Step 1.
  boost::asio::io_context io_context;

  // Step 2.
  boost::asio::ip::tcp protocol = boost::asio::ip::tcp::v6();

  // Step 3. Instantiating an acceptor socket object.
  boost::asio::ip::tcp::acceptor acceptor(io_context);
  boost::system::error_code ec;

  // Step 4. Opening the acceptor socket.
  acceptor.open(protocol, ec);

  if (ec.value() != 0) {
    // Failed to open the socket.
    std::cout
        << "Failed to open the acceptor socket!"
        << "Error code = "
        << ec.value() << ". Message: " << ec.message();
    return ec.value();
  }

  return 0;
}

int bind_acceptor_socket() {
  // Step 1.
  unsigned short port_num = 3333;

  // Step 2.
  boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address_v4::any(), port_num);

  boost::asio::io_context io_context;

  // Step 3. Creating and opening an acceptor socket.
  boost::asio::ip::tcp::acceptor acceptor(io_context, ep.protocol());
  boost::system::error_code ec;

  // Step 4. Binding the acceptor socket.
  acceptor.bind(ep, ec);

  // Handling errors if any.
  if (ec.value() != 0) {
    // Failed to bind the acceptor socket. Breaking
    // execution.
    std::cout << "Failed to bind the acceptor socket."
              << "Error code = " << ec.value() << ". Message: "
              << ec.message();

    return ec.value();
  }

  return 0;
}

int connect_to_end() {
  // Step 1.
  std::string raw_ip_address = "127.0.0.1";
  unsigned short port_num = 3333;

  try {
    // Step 2. Creating an endpoint designating a target server application.
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(raw_ip_address), port_num);
    boost::asio::io_context io_context;

    // Step 3. Creating and opening a socket.
    boost::asio::ip::tcp::socket sock(io_context, ep.protocol());

    // Step 4. Connecting a socket.
    sock.connect(ep);
  } catch (boost::system::system_error& e) {
    std::cout << "Error occured! Error code = " << e.code()
              << ". Message: " << e.what();

    return e.code().value();
  }
//  return 0;
}

int dns_connect_to_end() {
  // Step1.
  std::string host = "example host.book";
  std::string port_num = "3333";

  // Used by a 'resolver' and a 'socket'.
  boost::asio::io_context io_context;

  // Create a resolver
  boost::asio::ip::tcp::resolver::query resolver_query(host, port_num,
                                                       boost::asio::ip::tcp::resolver::query::numeric_service);
  boost::asio::ip::tcp::resolver resolver(io_context);

  try {
    // Step 2. Resolving a DNS name.
    boost::asio::ip::tcp::resolver::iterator iter =
        resolver.resolve(resolver_query);

    // Step 3. Creating a socket.
    boost::asio::ip::tcp::socket sock(io_context);

    // Step 4. asio::connect() method iterates over
    // each endpoint until successfully connects to one
    // of them. It will throw an exception if it fails
    // to connect to all the endpoints or if other
    // error occurs.
    boost::asio::connect(sock, iter);
  } catch (boost::system::system_error& e) {
    std::cout << "Error occured! Error code = " << e.code()
      << ". Message is : " << e.what();
    return e.code().value();
  }

  return 0;
}