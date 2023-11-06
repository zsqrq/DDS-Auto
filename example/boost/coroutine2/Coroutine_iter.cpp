#include <iostream>

#include "boost/coroutine2/all.hpp"
#include "boost/coroutine2/detail/pull_coroutine.hpp"
#include "boost/coroutine2/detail/push_coroutine.hpp"

void foo(boost::coroutines2::coroutine<int>::pull_type& sink) {
  using coIter = boost::coroutines2::coroutine<int>::pull_type::iterator;

  for (coIter start = begin(sink); start != end(sink); ++start) {
    std::cout << "retrieve " << *start << "\n";
  }
}

void foo2(boost::coroutines2::coroutine<int>::pull_type& sink) {
  for (auto val : sink) {
    std::cout << "retrieve " << val << std::endl;
  }
}

void foo3(boost::coroutines2::coroutine<int>::pull_type& sink) {
  for (int i = 0; i < 10; i++) {
    std::cout << "retrieve " << sink.get() << "\n";

    sink();
  }
}

int main(int argc, char* argv[]) {
  boost::coroutines2::coroutine<int>::push_type source(foo);
  for (int i = 0; i < 10; ++i) {
    source(i);
  }
  return 0;
}