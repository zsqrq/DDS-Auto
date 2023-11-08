//
// Created by wz on 23-11-8.
//
#include <iostream>
#include <cstdlib>
#include <set>
#include <memory>

#include "boost/asio.hpp"
#include "glog/logging.h"

using namespace boost;
constexpr int max_length = 1024;
using socket_ptr = std::shared_ptr<asio::ip::tcp::socket>;
std::set<std::shared_ptr<std::thread>> thread_set;

void session(socket_ptr sock) {
  try {
    for (;;) {
      char data[max_length];
      memset(data, '\0', max_length);
      boost::system::error_code error;
      size_t length = sock->read_some(boost::asio::buffer(data, max_length),error);

      if (error == boost::asio::error::eof) {
        LOG(WARNING) << "connection closed by peer";
        break;
      } else if (error) {
        throw boost::system::system_error(error);
      }
      LOG(INFO) << "Receive from " << sock->remote_endpoint().address().to_string();
      LOG(INFO) << "Received message is : " << data;

      boost::asio::write(*sock, boost::asio::buffer(data, length));
    }
  } catch (std::exception& e) {
    LOG(ERROR) << "Exception in thread: " << e.what() ;
  }
}

void server(boost::asio::io_context& io_context, unsigned short port) {
  asio::ip::tcp::acceptor acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port));
  for (;;) {
    socket_ptr socket(new asio::ip::tcp::socket(io_context));
    acceptor.accept(*socket);
    auto t = std::make_shared<std::thread>(session, socket);
    thread_set.insert(t);
  }
}

int main(int argc, char* argv[]) {
  try {
    boost::asio::io_context io_context;
    server(io_context, 10086);
    for (auto &t : thread_set) {
      if (t->joinable()) {
        t->join();
      }
    }
  } catch (std::exception& e) {
    LOG(ERROR) << "Exception " << e.what();
  }
  return 0;
}
