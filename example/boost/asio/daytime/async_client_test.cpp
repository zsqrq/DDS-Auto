#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::udp;

class udp_client {
 public:
  udp_client(boost::asio::io_context& io_context, const std::string& host,
             const std::string& port)
      : io_context_(io_context),
        socket_(io_context, udp::endpoint(udp::v4(), 0)),
        resolver_(io_context) {
    udp::resolver::query query(udp::v4(), host, port);
    receiver_endpoint_ = *resolver_.resolve(query);
  }

  void start_send() {
    std::string message = "Hello from the async UDP client!";
    socket_.async_send_to(boost::asio::buffer(message), receiver_endpoint_,
                          [this](boost::system::error_code ec,
                                 std::size_t /*bytes_transferred*/) {
                            if (!ec) {
                              start_receive();
                            }
                          });
  }

 private:
  void start_receive() {
    socket_.async_receive_from(
        boost::asio::buffer(recv_buffer_), sender_endpoint_,
        [this](boost::system::error_code ec, std::size_t bytes_transferred) {
          if (!ec) {
            std::cout.write(recv_buffer_.data(), bytes_transferred);
            std::cout << std::endl;
            start_send();
          }
        });
  }

  boost::asio::io_context& io_context_;
  udp::socket socket_;
  udp::resolver resolver_;
  udp::endpoint receiver_endpoint_;
  udp::endpoint sender_endpoint_;
  std::array<char, 1024> recv_buffer_;
};

int main(int argc, char* argv[]) {
  try {
    if (argc != 3) {
      std::cerr << "Usage: async_udp_client <host> <port>\n";
      return 1;
    }

    boost::asio::io_context io_context;

    udp_client client(io_context, argv[1], argv[2]);
    client.start_send();

    io_context.run();
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
