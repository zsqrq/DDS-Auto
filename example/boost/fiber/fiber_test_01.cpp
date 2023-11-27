//
// Created by wz on 23-11-27.
//
#include "boost/fiber/all.hpp"
#include "boost/context/continuation.hpp"
#include "glog/logging.h"

int main() {
  namespace ctx=boost::context;
  FLAGS_alsologtostderr =1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging("Fiber");
  int a, b;
  bool stop = false;
  boost::context::continuation source = boost::context::callcc([&a,&b, &stop](ctx::continuation &&sink) {
    a = 0;
    b = 1;
    for (;;) {
      if (stop) {
        break;
      }
      LOG(INFO) << "Called once";
//      std::cout << "Called once" << std::endl;
      sink = sink.resume();
      LOG(INFO) << "Called twice";
      int next = a + b;
      a = b;
      b = next;
    }

    return std::move(sink);
  });
  for (int j = 0; j < 10; ++j) {
    LOG(INFO) << a << " " << b <<", ";
    source = source.resume();
  }
  return 0;
}
