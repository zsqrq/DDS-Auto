//
// Created by wz on 23-12-25.
//
#include <iostream>
#include <thread>
#include <sstream>
#include <vector>
#include <numeric>
#include <algorithm>

#include "glog/logging.h"

void thread_work1(std::string str) {
  LOG(INFO) << "str is " << str;
}

class background_task {
 public:
  void operator()() {
    LOG(INFO) << "background_task called";
  }
};

struct func {
  int& _i;
  func(int& i) : _i(i){}

  void operator()() {
    for (int i = 0; i < 3; ++i) {
      _i = i;
      LOG(INFO) << "_i is " << _i;
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  }
};

void oops() {
  int local_state = 0;
  func myfunc(local_state);
  std::thread functhread(myfunc);
  LOG(INFO) << "oops detaching thread for func";
  functhread.detach();
}

void use_join() {
  int local_state = 0;
  func myfunc(local_state);
  std::thread functhread(myfunc);
  LOG(INFO) << "oops joinning thread for func";
  functhread.join();
}

void catch_exeption() {
  int local_state = 0;
  func myfunc(local_state);
  std::thread functhread {myfunc};

  try {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  catch (std::exception& e) {
    functhread.join();
    throw;
  }
  functhread.join();
}

class thread_guard {
 private:
  std::thread& _t;
 public:
  explicit thread_guard(std::thread& t) : _t(t) {}

  ~thread_guard() {
    if (_t.joinable()) {
      _t.join();
    }
  }

  thread_guard(thread_guard const&) = delete;
  thread_guard& operator = (thread_guard const&) = delete;
};

void auto_guard() {
  int local_guard = 0;
  func myfunc(local_guard);
  std::thread t{myfunc};
  thread_guard g(t);
  LOG(INFO)  << "auto guard finished ";
}

void print_str(int i, std::string const& s) {
  LOG(INFO) << "i is " << i << " str is " << s;
}

void danger_oops(int s_param) {
  char buffer[1024];
  sprintf(buffer, "%i", s_param);
//  LOG(INFO) << buffer << s_param;

  std::thread t(print_str, 3, std::string{buffer});
  t.detach();
  LOG(INFO) << "danger oops finished ";
}

void safe_oops(int s_param) {
  char buffer[1024];
  sprintf(buffer, "%i", s_param);
//  LOG(INFO) << buffer << s_param;

  std::thread t(print_str, 3, std::string{buffer});
  t.detach();
}

void change_param(int& param) {
  param++;
}

void ref_oops(int s_param) {
  LOG(INFO) << "before change , param is " << s_param;
  std::thread t2(change_param, std::ref(s_param));
  t2.join();
  LOG(INFO) << "after change , param is " << s_param;
}
class X
{
 public:
  void do_lengthy_work() {
    LOG(INFO) << "do_lengthy_work ";
  }
};

void bind_class_oops() {
  X my_x;
  std::thread t(&X::do_lengthy_work, std::ref(my_x));
  t.join();
}

void deal_unique(std::unique_ptr<int> p) {
  LOG(INFO) << "unique ptr data is :" << *p;
  (*p)++;
  LOG(INFO) << "after unique ptr data is " << *p;
}

void move_oops() {
  auto p = std::make_unique<int>(100);
  std::thread t(deal_unique, std::move(p));
  t.join();
}

int test_01() {
  std::string hellostr = "Hello World";
  std::thread t1(thread_work1, hellostr);
  t1.join();

  std::thread t2((background_task()));
  t2.join();

  std::thread t3{background_task()};
  t3.join();

  std::thread t4([](std::string str) {
    LOG(INFO) << "str is " << str;
  },hellostr);
  t4.join();

  oops();
  std::this_thread::sleep_for(std::chrono::seconds(2));

  use_join();

  catch_exeption();

  auto_guard();

  danger_oops(100);
  std::this_thread::sleep_for(std::chrono::seconds(2));

  safe_oops(100);
  std::this_thread::sleep_for(std::chrono::seconds(2));

  return 0;
}

void some_function() {
  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

void some_other_function() {
  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

void dagerous_use(){
  std::thread t1(some_function);

  auto t2 = std::move(t1);

  t1 = std::thread(some_other_function);
  std::thread t3;
  t3 = std::move(t2);
  t1 = std::move(t3);
  std::this_thread::sleep_for(std::chrono::seconds(50));
}

std::thread f(){
  return std::thread(some_function);
}

void param_function(int a) {
  while (true) {
    LOG(INFO) << "param is " << a;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

std::thread g() {
  std::thread t(param_function, 43);
  return t;
}

class Joining_thread {
  std::thread _t;
 public:
  Joining_thread() noexcept = default;
  template<typename Callable, typename ... Args>
  explicit Joining_thread(Callable&& func, Args&&... args):
      _t(std::forward<Callable>(func), std::forward<Args>(args)...){
    LOG(INFO) << "Callable Constructor is called";
  }
  explicit Joining_thread(std::thread t) noexcept: _t(std::move(t)){
    LOG(INFO) << "Thread move Constructor is called";
  }
  Joining_thread(Joining_thread&& other) noexcept: _t(std::move(other._t)){
    LOG(INFO) << "Assign Constructor is called";
  }

  Joining_thread& operator=(Joining_thread&& other) noexcept {
    LOG(INFO) << "Copy Assign Constructor is called";
    if (joinable()) {
      join();
    }
    _t = std::move(other._t);
    return *this;
  }

  Joining_thread& operator=(std::thread other) noexcept {
    LOG(INFO) << "Copy Move Assign Constructor is called";
    if (joinable()) {
      join();
    }
    _t = std::move(other);
    return *this;
  }

  ~Joining_thread() {
    if (joinable()) {
      join();
    }
  }

  void swap(Joining_thread& other) noexcept {
    _t.swap(other._t);
  }

  std::thread::id get_id() const noexcept {
    return _t.get_id();
  }

  bool joinable() const noexcept {
    return _t.joinable();
  }

  void join() {
    _t.join();
  }

  void detach() {
    _t.detach();
  }

  std::thread& as_thread() noexcept {
    return _t;
  }

  const std::thread& as_thread() const noexcept {
    return _t;
  }
};

void use_jointhread() {
  Joining_thread j1([](int maxindex) {
    for (int i = 0; i < maxindex; ++i) {
      LOG(INFO) << "in thread id " << std::this_thread::get_id()
                << " cur index is " << i;
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  }, 10);

  Joining_thread j2(std::thread([](int maxindex) {
    for (int i = 0; i < maxindex; i++) {
      LOG(INFO) << "in thread id " << std::this_thread::get_id()
                << " cur index is " << i;
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  }, 10));

  Joining_thread j3(std::thread([](int maxindex) {
    for (int i = 0; i < maxindex; i++) {
      LOG(INFO) << "in thread id " << std::this_thread::get_id()
                << " cur index is " << i ;
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  }, 10));

  j1 = std::move(j3);
}

void use_vector() {
  std::vector<std::thread> threads;
  for (unsigned i = 0; i < 10; ++i){
    threads.emplace_back(param_function, i);
  }

  for(auto& entry : threads) {
    entry.join();
  }
}

template<typename Iterator, typename T>
struct accumulate_block {
  void operator() (Iterator first, Iterator last, T& result) {
    result = std::accumulate(first, last, result);
  }
};

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init) {
  unsigned long const length = std::distance(first, last);
  if (!length) {
    return init;
  }
  unsigned long const min_per_thread = 25;
  unsigned long const max_threads = (length + min_per_thread - 1) / min_per_thread;
  unsigned long const hardware_threads = std::thread::hardware_concurrency();
  unsigned long const num_threads =
      std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
  LOG(INFO) << "Opening Thread Number is :  " << num_threads;
  unsigned long const block_size = length / num_threads;
  std::vector<T> results(num_threads);
  std::vector<std::thread> threads(num_threads - 1);
  Iterator block_start = first;

  for (unsigned long i = 0; i < (num_threads - 1); ++i) {
    Iterator block_end = block_start;
    std::advance(block_end, block_size);
    threads[i] = std::thread(
        accumulate_block<Iterator, T>(),
        block_start, block_end, std::ref(results[i]));
    block_start = block_end;
  }

  accumulate_block<Iterator, T>()(
      block_start, last, results[num_threads - 1]);

  for (auto& entry : threads) {
    entry.join();
  }
  return std::accumulate(results.begin(), results.end(), init);
}

void use_parallel_acc() {
  std::vector<int> vec(10000);
  for (int i = 0; i < 10000; ++i) {
    vec.push_back(i);
  }
  int sum = 0;
  sum = parallel_accumulate<std::vector<int>::iterator,int>(vec.begin(), vec.end(), sum);
  LOG(INFO) << "sum is " << sum;
}

void test_02() {
  use_parallel_acc();
  std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main(int argc, char** argv) {
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging(argv[0]);
//  test_01();
  use_jointhread();
  test_02();

  return 0;
}