#include <ctime>
#include <iostream>
#include <string>

#include "boost/asio.hpp"
#include "boost/bind/bind.hpp"
#include "boost/enable_shared_from_this.hpp"
#include "boost/shared_ptr.hpp"

std::string make_daytime_string() {
  auto now = std::time(0);
  return std::ctime(&now);
}

class tcp_connection : public boost::enable_shared_from_this<tcp_connection> {
 public:
  using pointer = boost::shared_ptr<tcp_connection>;

  static pointer create(boost::asio::io_context& io_context) {
    return pointer(new tcp_connection(io_context));
  }

  boost::asio::ip::tcp::socket& socket() { return socket_; }

  void start() {
    message_ = make_daytime_string();

    boost::asio::async_write(
        socket_, boost::asio::buffer(message_),
        boost::bind(&tcp_connection::handle_write, shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
  }

 private:
  tcp_connection(boost::asio::io_context& io_context) : socket_(io_context) {}

  void handle_write(const boost::system::error_code&, size_t) {}

  boost::asio::ip::tcp::socket socket_;
  std::string message_;
};

class tcp_server {
 public:
  tcp_server(boost::asio::io_context& io_context)
      : io_context_(io_context),
        acceptor_(io_context, boost::asio::ip::tcp::endpoint(
                                  boost::asio::ip::tcp::v4(), 13)) {
    start_accept();
  }

 private:
  void start_accept() {
    auto new_connection = tcp_connection::create(io_context_);

    acceptor_.async_accept(
        new_connection->socket(),
        boost::bind(&tcp_server::handle_accept, this, new_connection,
                    boost::asio::placeholders::error()));
  }

  void handle_accept(tcp_connection::pointer new_connection,
                     const boost::system::error_code& error) {
    if (!error) {
      new_connection->start();
    }
    start_accept();
  }

 private:
  boost::asio::io_context& io_context_;
  boost::asio::ip::tcp::acceptor acceptor_;
};

int main(int argc, char* argv[]) {
  try {
    boost::asio::io_context io_context;
    tcp_server server(io_context);
    io_context.run();
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}