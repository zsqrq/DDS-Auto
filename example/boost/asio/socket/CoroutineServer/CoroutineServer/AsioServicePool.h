//
// Created by wz on 23-11-24.
//

#ifndef FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_COROUTINESERVER_COROUTINESERVER_ASIOSERVICEPOOL_H_
#define FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_COROUTINESERVER_COROUTINESERVER_ASIOSERVICEPOOL_H_
#include <vector>
#include <boost/asio.hpp>
class AsioIOServicePool
{
 public:
  using IOService = boost::asio::io_context;
  using Work = boost::asio::io_context::work;
  using WorkPtr = std::unique_ptr<Work>;
  ~AsioIOServicePool();
  AsioIOServicePool(const AsioIOServicePool&) = delete;
  AsioIOServicePool& operator=(const AsioIOServicePool&) = delete;
  boost::asio::io_context& GetIOService();
  void Stop();

  static AsioIOServicePool& GetInstance();
 private:
  AsioIOServicePool(std::size_t size = std::thread::hardware_concurrency());
  std::vector<IOService> _ioServices;
  std::vector<WorkPtr> _works;
  std::vector<std::thread> _threads;
  std::size_t _nextIOService;

};

#endif //FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_COROUTINESERVER_COROUTINESERVER_ASIOSERVICEPOOL_H_
