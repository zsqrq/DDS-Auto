//
// Created by wz on 23-11-24.
//

#include "AsioServicePool.h"
#include "glog/logging.h"

using namespace std;
AsioIOServicePool::AsioIOServicePool(std::size_t size):_ioServices(size),
                                                       _works(size), _nextIOService(0){
  for (std::size_t i = 0; i < size; ++i) {
    _works[i] = std::unique_ptr<Work>(new Work(_ioServices[i]));
  }

  //遍历多个ioservice，创建多个线程，每个线程内部启动ioservice
  for (std::size_t i = 0; i < _ioServices.size(); ++i) {
    _threads.emplace_back([this, i]() {
      _ioServices[i].run();
    });
  }
}

AsioIOServicePool::~AsioIOServicePool() {
  LOG(INFO) << "AsioIOServicePool destruct";
}

boost::asio::io_context& AsioIOServicePool::GetIOService() {
  auto& service = _ioServices[_nextIOService++];
  if (_nextIOService == _ioServices.size()) {
    _nextIOService = 0;
  }
  return service;
}

void AsioIOServicePool::Stop(){
  for (auto& work : _works) {
    work.reset();
  }

  for (auto& t : _threads) {
    t.join();
  }
}

AsioIOServicePool& AsioIOServicePool::GetInstance() {
  static AsioIOServicePool instance(1);
  return instance;
}
