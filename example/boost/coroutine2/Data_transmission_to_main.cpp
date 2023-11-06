#include <iostream>

#include "boost/coroutine2/all.hpp"

void data_trans(boost::coroutines2::coroutine<int>::push_type& sink) {
  std::cout << " coroutine 1" << std::endl;

  sink(1);  // push {1} back to main-context

  std::cout << " coroutine 2" << std::endl;

  sink(2);

  std::cout << " coroutine 3" << std::endl;

  sink(3);
}

int main(int argc, char* argv[]) {
  typedef boost::coroutines2::coroutine<int> coro_t2;

  coro_t2::pull_type source(data_trans);

  while (source) {
    auto ret = source.get();  // pushed sink() data

    std::cout << "move to coroutine-function " << ret << std::endl;

    source();  // context-switch to coroutine-function

    std::cout << "back from coroutine-function " << std::endl;
  }
  return 0;
}