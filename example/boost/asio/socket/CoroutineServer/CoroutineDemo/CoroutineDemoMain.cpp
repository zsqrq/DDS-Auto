//
// Created by wz on 23-11-23.
//
#include <cstdio>
#include "boost/asio.hpp"
#include "boost/asio/awaitable.hpp"
#include "boost/asio/co_spawn.hpp"
#include "boost/asio/detached.hpp"
#include "boost/asio/io_context.hpp"
#include "boost/asio/ip/tcp.hpp"
#include "boost/asio/signal_set.hpp"
#include "boost/asio/write.hpp"
#include "glog/logging.h"

using boost::asio::awaitable;
using boost::asio::co_spawn;
using boost::asio::detached;
using boost::asio::use_awaitable;
using boost::asio::ip::tcp;
namespace this_coro = boost::asio::this_coro;

#if defined(BOOST_ASIO_ENABLE_HANDLER_TRACKING)
#define use_awaitable \
  boost::asio::use_awaitable_t(__FILE__, __LINE__, __PRETTY_FUNCTION__)
#endif

boost::asio::awaitable<void> echo(tcp::socket socket) {
  try {
    char data[1024];
    for (;;) {
      std::size_t n = co_await socket.async_read_some(boost::asio::buffer(data),
                                                      use_awaitable);
      co_await boost::asio::async_write(socket, boost::asio::buffer(data, n),
                                        use_awaitable);
    }
  } catch (std::exception& e) {
    LOG(ERROR) << "echo Exception: " << e.what();
  }
}

namespace LaoWang {
template<typename T>
constexpr typename std::remove_reference<T>::type&&
YeahMove(T&& arg) noexcept
{ return static_cast<typename std::remove_reference<T>::type&&>(arg); }
}

awaitable<void> listener() {
  auto executor = co_await boost::asio::this_coro::executor;
  tcp::acceptor acceptor(executor, {tcp::v4(), 10086});
  for (;;) {
    tcp::socket socket = co_await acceptor.async_accept(use_awaitable);
    co_spawn(executor, echo(LaoWang::YeahMove(socket)), detached);
  }
}

int main(int argc, char* argv[]) {
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging(argv[0]);

  try {
    boost::asio::io_context io_context(1);
    boost::asio::signal_set signals(io_context, SIGINT, SIGTERM);
    signals.async_wait([&](auto, auto) { io_context.stop(); });
    co_spawn(io_context, listener(), detached);
    io_context.run();
  } catch (std::exception& e) {
    LOG(ERROR) << "Exception: " << e.what();
  }
  return 0;
}