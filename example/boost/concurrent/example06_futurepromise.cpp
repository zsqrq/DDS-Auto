//
// Created by wz on 24-1-8.
//
#include <iostream>
#include <future>
#include <chrono>
#include <string>

#include "glog/logging.h"
#include "threadpool.h"

std::string fetchDataFromDB(std::string query) {
  LOG(INFO) << "fetchDataFromDB Starting ......";
  std::this_thread::sleep_for(std::chrono::seconds(5));
  return "Data : " + query;
}

void use_async() {
  std::future<std::string> resultFromDB = std::async(std::launch::async, fetchDataFromDB, "Data");
  LOG(INFO) << "Doing something else...";
  std::string dbdata = resultFromDB.get();
  LOG(INFO) << dbdata;
}

int my_task() {
  LOG(INFO) << "my task starting ......";
  std::this_thread::sleep_for(std::chrono::seconds(5));
  LOG(INFO) << "my task run 5 s";
  return 42;
}

void use_package() {
  std::packaged_task<int()> task(my_task);

  std::future<int> result = task.get_future();
  std::thread t(std::move(task));
  LOG(INFO) << "use_package ready to detach....";
  t.detach();
  int res = result.get();
  LOG(INFO) << "The result is: " << res;
}

void myFunction(std::promise<int>&& promise) {
  LOG(INFO) <<  "myFunction Starting set value ...... ";
  std::this_thread::sleep_for(std::chrono::seconds(5));
  promise.set_value(41);
  LOG(INFO) <<  "myFunction runs 5 seconds ...";
}

void threadFunction(std::shared_future<int> future) {
  LOG(INFO) <<  "threadFunction Starting .....";
  try {
    int result = future.get();
    LOG(INFO) <<  "threadFunction get Result: " << result;
  } catch (const std::future_error& e) {
    LOG(ERROR) << "Future error: " << e.what();
  }
}

void use_shared_future() {
  std::promise<int> promise;
  std::shared_future<int> future = promise.get_future();

  std::thread myThread1(myFunction, std::move(promise));
  std::thread myThread2(threadFunction, future);
  std::thread myThread3(threadFunction, future);

  myThread1.join();
  myThread2.join();
  myThread3.join();
}

void use_shared_future_error() {
  std::promise<int> promise;
  std::shared_future<int> future = promise.get_future();

  std::thread myThread1(myFunction, std::move(promise));
  std::thread myThread2(threadFunction, std::move(future));
  std::thread myThread3(threadFunction, std::move(future));

  myThread1.join();
  myThread2.join();
  myThread3.join();
}

void set_value(std::promise<int> prom) {
  LOG(INFO) << "Starting Seting Value";
  std::this_thread::sleep_for(std::chrono::seconds(5));
  prom.set_value(10);
  LOG(INFO) << "promise set value success";
}

void use_promise() {
  std::promise<int> prom;
  std::future<int> fut = prom.get_future();
  std::thread t(set_value, std::move(prom));
  LOG(INFO) << "Waiting for the thread to set the value...";
  LOG(INFO) << "Value set by the thread: " << fut.get();
  t.join();
}

void set_exception(std::promise<void> prom) {
  try {
    throw std::runtime_error("An error occurred !");
  } catch (...) {
    prom.set_exception(std::current_exception());
  }
}

void use_promise_exception() {
  std::promise<void> prom;
  std::future<void> fut = prom.get_future();
  std::thread t(set_exception, std::move(prom));

  try {
    LOG(INFO) << "Waiting for the thread to set the exception...\n";
    fut.get();
  }
  catch (const std::exception& e) {
    LOG(ERROR) << "Exception set by the thread: " << e.what();
  }
  t.join();
}

void use_promise_destruct() {
  std::thread t;
  std::future<int> fut;

  {
    std::promise<int> prom;
    fut = prom.get_future();
    t = std::thread(set_value, std::move(prom));
  }
  LOG(INFO) << "Waiting for the thread to set the value...";
  LOG(INFO) << "Value set by the thread: " << fut.get();

  t.join();
}

void may_throw() {
  throw std::runtime_error("Oops, something went wrong!");
}

void use_future_exception() {
  std::future<void> result(std::async(std::launch::async, may_throw));
  try {
    result.get();
  }
  catch (const std::exception& e) {
    LOG(ERROR) << "Caught exception: " << e.what();
  }
}

int main(int argc, char* argv[]) {
  FLAGS_minloglevel = 0;
  FLAGS_alsologtostderr = 1;
  google::InitGoogleLogging(argv[0]);
  use_async();
  use_package();
  use_shared_future();
  use_shared_future_error();
  use_promise();
  use_promise_exception();
  use_promise_destruct();
  use_future_exception();
  return 0;
}
