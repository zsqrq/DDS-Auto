//
// Created by wz on 23-11-22.
//

#include "AsioThreadPool.h"

AsioThreadPool::AsioThreadPool(int threadNum ):_work(new boost::asio::io_context::work(_service)){
  for (int i = 0; i < threadNum; ++i) {
    _threads.emplace_back([this]() {
      _service.run();
    });
  }
}

boost::asio::io_context& AsioThreadPool::GetIOService() {
  return _service;
}

void AsioThreadPool::Stop() {
  _service.stop();
  _work.reset();
  for (auto& t : _threads) {
    t.join();
  }
}
