#include <iostream>

#include "boost/asio.hpp"
#include "boost/bind/bind.hpp"

void Print(const boost::system::error_code&, boost::asio::steady_timer* t,
           int* count) {
  if (*count < 5) {
    std::cout << *count << std::endl;
    ++(*count);
    t->expires_at(t->expiry() + boost::asio::chrono::seconds(5));
    t->async_wait(
        boost::bind(Print, boost::asio::placeholders::error, t, count));
  }
}

int main(int argc, char** argv) {
  boost::asio::io_context io;
  int count = 0;
  boost::asio::steady_timer t(io, boost::asio::chrono::seconds(1));
  t.async_wait(
      boost::bind(Print, boost::asio::placeholders::error, &t, &count));
  io.run();
  std::cout << "Final count is " << count << std::endl;
  return 0;
}
