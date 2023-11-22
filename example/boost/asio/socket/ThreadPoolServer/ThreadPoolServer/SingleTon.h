//
// Created by wz on 23-11-22.
//

#ifndef FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_IOCONTEXTPOOLSERVER_IOCONTEXTPOOLSERVER_SINGLETON_H_
#define FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_IOCONTEXTPOOLSERVER_IOCONTEXTPOOLSERVER_SINGLETON_H_
#include <memory>
#include <mutex>
#include <iostream>
#include "glog/logging.h"
using namespace std;

template<typename T>
class SingleTon {
 protected:
  SingleTon() = default;
  SingleTon(const SingleTon<T>&) = delete;
  SingleTon& operator=(const SingleTon<T>& single_ton) = delete;
  static inline std::shared_ptr<T> _instace {nullptr};

 public:
  static std::shared_ptr<T> GetInstance() {
    static std::once_flag s_flag;
    std::call_once(s_flag,[&](){
      _instace = std::shared_ptr<T>(new T);
    });
    return _instace;
  }

  void PrintAddress() {
    LOG(INFO) << _instace.get();
  }
  ~SingleTon() {
    LOG(INFO) << "this is singleton destruct";
  }
};

#endif  // FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_IOCONTEXTPOOLSERVER_IOCONTEXTPOOLSERVER_SINGLETON_H_
