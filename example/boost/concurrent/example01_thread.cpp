//
// Created by wz on 23-12-25.
//
#include <iostream>
#include <thread>
#include <sstream>
#include <vector>
#include <numeric>

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
  functhread.detach();
}

void use_join() {
  int local_state = 0;
  func myfunc(local_state);
  std::thread functhread(myfunc);
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
  LOG(INFO) << buffer << s_param;

  std::thread t(print_str, 3, std::string{buffer});
  t.detach();
}

void safe_oops(int s_param) {
  char buffer[1024];
  LOG(INFO) << buffer << s_param;

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

int main(int argc, char** argv) {
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging(argv[0]);
  test_01();

  return 0;
}