//
// Created by wz on 24-1-1.
//
#include <iostream>
#include <mutex>
#include <memory>
#include <queue>
#include <condition_variable>

#include "glog/logging.h"

int num = 1;
int num2 = 1;
std::mutex mtx_num;
std::mutex mtx_num2;
std::condition_variable cvA;
std::condition_variable cvB;

void PoorImplemention() {
  std::thread t1([]() {
    for (;;) {
      {
        std::lock_guard<std::mutex> lock(mtx_num);
        if (num == 1) {
          LOG(INFO) << "PoorImplemention thread A print 1.....";
          num++;
          continue;
        }
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
  });

  std::thread t2([]() {
    for (;;) {

      {
        std::lock_guard<std::mutex> lock(mtx_num);
        if (num == 2) {
          LOG(INFO) << "PoorImplemention thread B print 2.....";
          num--;
          continue;
        }
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
  });
  t1.join();
  t2.join();
}

void ResonableImplemention() {
  std::thread t1([]() {
    for (;;) {
      std::unique_lock<std::mutex> lock(mtx_num2);
      cvA.wait(lock,[]() {
        return num2 == 1;
      });
      num2++;
      LOG(INFO) << "ResonableImplemention thread A print 1.....";
      cvB.notify_one();
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
  });

  std::thread t2([]() {
    for (;;) {

      std::unique_lock<std::mutex> lock(mtx_num2);
      cvB.wait(lock, []() {
        return num2 == 2;
      });

      num2--;
      LOG(INFO) << "ResonableImplemention thread B print 2.....";
      cvA.notify_one();
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

  });
  t1.join();
  t2.join();
}

template<typename T>
class threadsafe_queue {
 private:
  mutable std::mutex mut;
  std::queue<T> data_queue;
  std::condition_variable data_cond;
 public:
  threadsafe_queue(){}
  threadsafe_queue(threadsafe_queue const& other) {
    std::lock_guard<std::mutex> lock(other.mut);
    data_queue = other.data_queue;
  }

  void push(T new_value) {
    std::lock_guard<std::mutex> lock(mut);
    data_queue.push(new_value);
    data_cond.notify_one();
  }
  void wait_and_pop(T& value) {
    std::unique_lock<std::mutex> lock(mut);
    data_cond.wait(lock,[this]{return !data_queue.empty();});
    value = data_queue.front();
    data_queue.pop();
  }
  std::shared_ptr<T> wait_and_pop() {
    std::unique_lock<std::mutex> lock(mut);
    data_cond.wait(lock, [this]{return !data_queue.empty();});
    std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
    data_queue.pop();
    return res;
  }
  bool try_pop(T& value) {
    std::lock_guard<std::mutex> lock(mut);
    if (data_queue.empty()) {
      return false;
    }
    value = data_queue.front();
    data_queue.pop();
    return true;
  }
  std::shared_ptr<T> try_pop() {
    std::lock_guard<std::mutex> lock(mut);
    if (data_queue.empty()) {
      return std::shared_ptr<T>();
    }
    std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
    data_queue.pop();
    return res;
  }
  bool empty() const {
    std::lock_guard<std::mutex> lock(mut);
    return data_queue.empty();
  }
};

void test_safe_que() {
  threadsafe_queue<int> safe_que;
  std::mutex mtx_print;
  std::thread producer([&]() {
    for (int i = 0;;++i) {
      safe_que.push(i);
      {
        std::lock_guard<std::mutex> printlock(mtx_print);
        LOG(INFO) << "test_safe_que producer push data is " << i;
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
  });

  std::thread consumer1([&]() {
    for (;;) {
      auto data = safe_que.wait_and_pop();
      {
        std::lock_guard<std::mutex> printlock(mtx_print);
        LOG(INFO) << "test_safe_que consumer1 wait and pop data is " << *data;
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
  });

  std::thread consumer2([&]() {
    for (;;) {
      auto data = safe_que.try_pop();
      if (data != nullptr) {
        {
          std::lock_guard<std::mutex> lock(mtx_print);
          LOG(INFO) << "test_safe_que consumer2 try_pop data is " << *data;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
      }
    }
  });
  producer.join();
  consumer1.join();
  consumer2.join();
}

int main(int argc, char** argv) {
  FLAGS_minloglevel = 0;
  FLAGS_alsologtostderr = 1;
  google::InitGoogleLogging(argv[0]);

  std::thread t1(PoorImplemention);
  std::thread t2(ResonableImplemention);
  std::thread t3(test_safe_que);

//  PoorImplemention();
//  ResonableImplemention();
//  test_safe_que();

  t1.join();
  t2.join();
  t3.join();
  return 0;
}


















