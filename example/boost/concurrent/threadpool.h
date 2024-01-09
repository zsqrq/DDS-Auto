//
// Created by wz on 24-1-8.
//

#ifndef FAST_DDS_EXAMPLE_EXAMPLE_BOOST_CONCURRENT_THREADPOOL_H_
#define FAST_DDS_EXAMPLE_EXAMPLE_BOOST_CONCURRENT_THREADPOOL_H_
#include <atomic>
#include <condition_variable>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
#include <functional>
#include "glog/logging.h"

class ThreadPool  {
 public:
  ThreadPool(const ThreadPool&) = delete;
  ThreadPool&        operator=(const ThreadPool&) = delete;

  static ThreadPool& instance() {
    static ThreadPool ins;
    return ins;
  }
  using Task = std::packaged_task<void()>;
  ~ThreadPool() {
    stop();
  }

  template<typename F, typename... Args>
  auto commit(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
    using RetType = decltype(f(args...));
    if (stop_.load()) {
      return std::future<RetType>{};
    }
    auto task = std::make_shared<std::packaged_task<RetType>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
    std::future<RetType> ret = task->get_future();
    {
      std::lock_guard<std::mutex> lock(cv_mtx_);
      tasks_.emplace([task]{(*task)();});
    }
    cv_lock_.notify_one();
    return ret;
  }

 private:
  ThreadPool(unsigned int num = 5) : stop_(false){
    if (num < 1) {
      thread_num_ = 1;
    } else {
      thread_num_ = num;
    }
    start();
  }

  void start() {
    for (int i = 0; i < thread_num_; ++i) {
      pool_.emplace_back([this]() {
        while (!this->stop_.load()) {
          Task task;
          {
            std::unique_lock<std::mutex> lock(cv_mtx_);
            this->cv_lock_.wait(lock,[this]{
              return this->stop_.load() || !this->tasks_.empty();
            });
            if (this->tasks_.empty()) return ;
            task = std::move(this->tasks_.front());
            this->tasks_.pop();
          }
          this->thread_num_--;
          task();
          this->thread_num_++;
        }
      });
    }
  }

  void stop() {
    stop_.store(true);
    cv_lock_.notify_all();
    for (auto& td : pool_) {
      if (td.joinable()) {
        LOG(INFO) << "join thread " << td.get_id();
        td.join();
      }
    }
  }

 private:
  std::mutex cv_mtx_;
  std::condition_variable cv_lock_;
  std::atomic_bool stop_;
  std::atomic_int thread_num_;
  std::queue<Task> tasks_;
  std::vector<std::thread> pool_;
};

#endif //FAST_DDS_EXAMPLE_EXAMPLE_BOOST_CONCURRENT_THREADPOOL_H_
