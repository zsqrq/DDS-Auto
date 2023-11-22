//
// Created by wz on 23-11-22.
//

#ifndef FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_IOCONTEXTPOOLSERVER_IOCONTEXTPOOLSERVER_ASIOIOSERVICEPOOL_H_
#define FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_IOCONTEXTPOOLSERVER_IOCONTEXTPOOLSERVER_ASIOIOSERVICEPOOL_H_
#include <vector>
#include "boost/asio.hpp"
#include "SingleTon.h"

class AsioIOServicePool : public SingleTon<AsioIOServicePool> {
  friend class SingleTon<AsioIOServicePool>;
 public:
  using IOService = boost::asio::io_context;
  using Work = boost::asio::io_context::work;
  using WorkPtr = std::unique_ptr<Work>;
  ~AsioIOServicePool();
  AsioIOServicePool(const AsioIOServicePool&) = delete;
  AsioIOServicePool& operator=(const AsioIOServicePool& ) = delete;
  boost::asio::io_context& GetIOService();
  void Stop();

 private:
  AsioIOServicePool(size_t size = std::thread::hardware_concurrency());
  std::vector<IOService> _ioServices;
  std::vector<WorkPtr> _works;
  std::vector<std::thread> _threads;
  std::size_t _nextIOService;
};

#endif  // FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_IOCONTEXTPOOLSERVER_IOCONTEXTPOOLSERVER_ASIOIOSERVICEPOOL_H_
