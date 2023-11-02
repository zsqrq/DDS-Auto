#include <ctime>
#include <iostream>
#include <string>

#include "boost/array.hpp"
#include "boost/asio.hpp"

std::string make_daytime_string() {
  std::time_t now = std::time(0);
  return std::ctime(&now);
}

int main(int argc, char** argv) {
  try {
    boost::asio::io_context io_context;
    boost::asio::ip::udp::socket socket(
        io_context,
        boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 13));

    for (;;) {
      boost::array<char, 1> recv_buf;
      boost::asio::ip::udp::endpoint remote_endpoint;
      socket.receive_from(boost::asio::buffer(recv_buf), remote_endpoint);

      std::string message = make_daytime_string();
      boost::system::error_code ignored_error;
      socket.send_to(boost::asio::buffer(message), remote_endpoint, 0,
                     ignored_error);
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
  return 0;
}