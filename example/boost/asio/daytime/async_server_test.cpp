#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::udp;

class udp_server {
 public:
  udp_server(boost::asio::io_context& io_context, unsigned short port)
      : socket_(io_context, udp::endpoint(udp::v4(), port)) {
    start_receive();
  }

 private:
  void start_receive() {
    socket_.async_receive_from(
        boost::asio::buffer(recv_buffer_), remote_endpoint_,
        [this](boost::system::error_code ec, std::size_t bytes_transferred) {
          if (!ec) {
            send_message(remote_endpoint_, "Hello from async UDP server");
            start_receive();  // Start receive to listen for next incoming
                              // datagram.
          }
        });
  }

  void send_message(const udp::endpoint& target_endpoint,
                    const std::string& message) {
    socket_.async_send_to(boost::asio::buffer(message), target_endpoint,
                          [](boost::system::error_code /*ec*/,
                             std::size_t /*bytes_transferred*/) {
                            // Handle errors if required
                            // For this example, we are not handling the error.
                          });
  }

  udp::socket socket_;
  udp::endpoint remote_endpoint_;
  std::array<char, 1024> recv_buffer_;
};

int main(int argc, char* argv[]) {
  try {
    if (argc != 2) {
      std::cerr << "Usage: async_udp_server <port>\n";
      return 1;
    }

    boost::asio::io_context io_context;
    udp_server server(io_context, std::atoi(argv[1]));

    io_context.run();
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
