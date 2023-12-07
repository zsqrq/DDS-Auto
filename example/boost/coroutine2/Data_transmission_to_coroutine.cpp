#include <iostream>

#include "boost/coroutine2/all.hpp"

void foo(boost::coroutines2::coroutine<std::string>::pull_type& sink) {
  while (sink) {  // Continue as long as there are values to pull
    std::string value = sink.get();  // Get the current value
    std::cout << "get " << value << " from main() \n";
    sink();  // Yield back to the push_type to get the next value
  }
}

int main(int argc, char* arhv[]) {
  std::string str1{"hello"};
  std::string str2{"world"};

  boost::coroutines2::coroutine<std::string>::push_type source(foo);

  std::cout << "pass " << str1 << " to foo()\n";
  source(str1);
  source(str2);

  std::cout << "pass " << str2 << " to foo()\n";
  source(str1);
  source(str2);

  return 0;
}
