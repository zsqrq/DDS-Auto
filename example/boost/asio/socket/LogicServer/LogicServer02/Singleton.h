//
// Created by wz on 23-11-21.
//

#ifndef FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_LOGICSERVER_LOGICSERVER01_SINGLETON_H_
#define FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_LOGICSERVER_LOGICSERVER01_SINGLETON_H_
#include <memory>
#include <iostream>
#include <mutex>
#include "glog/logging.h"

template<typename T>
class Singleton {
 public:
  static std::shared_ptr<T> GetInstance() {
    static std::once_flag s_flag;
    std::call_once(s_flag, [&]() {
      _instance = std::shared_ptr<T>(new T);
    });
    return _instance;
  }

  void PrintAddress() {
    LOG(INFO) << _instance.get();
  }

  ~Singleton() {
    LOG(INFO) << "This is singleton destruct";
  }
 protected:
  Singleton() = default;
  Singleton(const Singleton<T>&) = delete;
  Singleton& operator=(const Singleton<T>& st) = delete;

  static inline std::shared_ptr<T> _instance = nullptr;
};

#endif  // FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_LOGICSERVER_LOGICSERVER01_SINGLETON_H_
