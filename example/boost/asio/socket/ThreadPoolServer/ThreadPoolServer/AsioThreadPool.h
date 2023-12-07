//
// Created by wz on 23-11-22.
//

#ifndef FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_THREADPOOLSERVER_THREADPOOLSERVER_ASIOTHREADPOOL_H_
#define FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_THREADPOOLSERVER_THREADPOOLSERVER_ASIOTHREADPOOL_H_
#include "SingleTon.h"
#include "boost/asio.hpp"

class AsioThreadPool : public SingleTon<AsioThreadPool> {
 public:
  friend class SingleTon<AsioThreadPool>;
  ~AsioThreadPool(){}
  AsioThreadPool& operator=(const AsioThreadPool&) = delete;
  AsioThreadPool(const AsioThreadPool&) = delete;
  boost::asio::io_context& GetIOService();
  void Stop();
 private:
  AsioThreadPool(int threadNum = std::thread::hardware_concurrency());
  boost::asio::io_context _service;
  std::unique_ptr<boost::asio::io_context::work> _work;
  std::vector<std::thread> _threads;
};

#endif //FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_THREADPOOLSERVER_THREADPOOLSERVER_ASIOTHREADPOOL_H_
