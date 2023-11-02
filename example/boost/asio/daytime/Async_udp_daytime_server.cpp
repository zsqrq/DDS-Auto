#include <ctime>
#include <iostream>
#include <string>

#include "boost/array.hpp"
#include "boost/asio.hpp"
#include "boost/bind/bind.hpp"
#include "boost/shared_ptr.hpp"

using boost::asio::ip::udp;

std::string make_daytime_string() {
  using namespace std;  // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}

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
        boost::bind(&udp_server::handle_receive, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
  }

  void handle_receive(const boost::system::error_code& error, std::size_t) {
    if (!error) {
      boost::shared_ptr<std::string> message(
          new std::string(make_daytime_string()));
      socket_.async_send_to(
          boost::asio::buffer(*message), remote_endpoint_,
          boost::bind(&udp_server::handle_send, this,
                      boost::asio::placeholders::error,
                      boost::asio::placeholders::bytes_transferred));
      start_receive();
    }
  }

  void handle_send(const boost::system::error_code&, std::size_t) {}

 private:
  udp::socket socket_;
  udp::endpoint remote_endpoint_;
  boost::array<char, 1024> recv_buffer_;
};

int main(int argc, char* argv[]) {
  try {
    boost::asio::io_context io_context;
    udp_server server(io_context, std::atoi(argv[1]));
    io_context.run();
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}