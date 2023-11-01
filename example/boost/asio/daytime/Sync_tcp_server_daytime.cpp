#include <boost/asio.hpp>
#include <ctime>
#include <iostream>
#include <string>

std::string make_daytime_string() {
  auto now = std::time(0);
  return std::ctime(&now);
}

int main(int argc, char* argv[]) {
  try {
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::acceptor acceptor(
        io_context,
        boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 13));

    for (;;) {
      boost::asio::ip::tcp::socket socket(io_context);
      acceptor.accept(socket);

      std::string message = make_daytime_string();

      boost::system::error_code ignored_error;
      boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}
