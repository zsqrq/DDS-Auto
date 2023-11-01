#include <iostream>

#include "boost/asio.hpp"

void print_err(const boost::system::error_code&) {
  std::cout << "Hello Timer Async " << std::endl;
}

int main(int argc, char** argv) {
  boost::asio::io_context io;
  boost::asio::steady_timer t(io, boost::asio::chrono::seconds(5));
  t.async_wait(&print_err);
  io.run();
  return 0;
}