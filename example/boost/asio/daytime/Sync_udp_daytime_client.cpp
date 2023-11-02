#include <array>
#include <iostream>

#include "boost/array.hpp"
#include "boost/asio.hpp"
#include "boost/container/vector.hpp"

int main(int argc, char** argv) {
  for (int i = 0; i < 10; ++i) {
    try {
      if (argc != 2) {
        std::cerr << "Usage : client <host>" << std::endl;
        return 1;
      }
      boost::asio::io_context io_context;

      boost::asio::ip::udp::resolver resolver(io_context);
      boost::asio::ip::udp::endpoint receiver_endpoint =
          *resolver.resolve(boost::asio::ip::udp::v4(), argv[1], "daytime")
               .begin();

      boost::asio::ip::udp::socket socket(io_context);
      // boost::asio::socket_base::reuse_address option(true);
      // socket.set_option(option);
      socket.open(boost::asio::ip::udp::v4());
      boost::array<char, 1> send_buf = {{0}};
      socket.send_to(boost::asio::buffer(send_buf), receiver_endpoint);
      // socket.async_receive_from

      boost::array<char, 128> recv_buf;
      boost::container::vector<char> recv_buf1;
      boost::asio::ip::udp::endpoint sender_endpoint;
      size_t len =
          socket.receive_from(boost::asio::buffer(recv_buf), sender_endpoint);

      std::cout.write(recv_buf.data(), len);
    } catch (const std::exception& e) {
      std::cerr << e.what() << '\n';
    }
  }
}