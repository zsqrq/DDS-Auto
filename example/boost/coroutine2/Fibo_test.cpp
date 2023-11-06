#include <iostream>

#include "boost/coroutine2/all.hpp"

void foo(boost::coroutines2::coroutine<void>::push_type& sink) {
  std::cout << "a = ";
  sink();
  std::cout << "b = ";
  sink();
  std::cout << "c = ";
}

void fibo(boost::coroutines2::coroutine<int>::push_type& sink) {
  int first = 1, second = 1;
  sink(first);
  sink(second);
  for (int i = 0; i < 8; ++i) {
    int third = first + second;
    first = second;
    second = third;
    sink(third);
  }
}

void print1(boost::coroutines2::coroutine<int>::push_type& apush) {
  for (int i = 0; i < 10; i++) {
    std::cout << "---------------------"
              << "coroutine 1" << std::endl;
    apush(1);
  }
}

void print2(boost::coroutines2::coroutine<int>::push_type& apush) {
  for (int i = 0; i < 10; i++) {
    std::cout << "---------------------"
              << "coroutine 2" << std::endl;
    apush(1);
  }
}

int main(int argc, char* argv[]) {
  /*
   * 斐波那契数列
   */
  boost::coroutines2::coroutine<int>::pull_type apull(print1);

  boost::coroutines2::coroutine<int>::pull_type apull2(print2);

  for (int i = 0; i < 10; ++i) {
    apull.get();
    apull();
    apull2.get();
    apull2();
  }
  std::cout << "continue>>>" << std::endl;

  return 0;
}