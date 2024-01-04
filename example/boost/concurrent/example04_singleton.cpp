//
// Created by wz on 24-1-1.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <memory>

#include "glog/logging.h"

class Single2 {
 private:
  Single2() {}
  Single2(const Single2&) = delete;
  Single2& operator=(const Single2&) = delete;

 public:
  static Single2& GetInstance() {
    static Single2 single;
    return single;
  }
};

void test_singleton2() {
  LOG(INFO) << "s1 addr is " << &Single2::GetInstance;
  LOG(INFO) << "s2 addr is " << &Single2::GetInstance;
}

class Single2Hungry {
 private:
  Single2Hungry(){}
  Single2Hungry& operator=(const Single2Hungry&) = delete;
 private:
  static Single2Hungry* single;

 public:
  static Single2Hungry* GetInstance() {
    if (single == nullptr) {
      single = new Single2Hungry();
    }
    return single;
  }
};
Single2Hungry* Single2Hungry::single = Single2Hungry::GetInstance();

void thread_func_single2hungry(int n) {
  LOG(INFO) << "this is thread " << n;
  LOG(INFO) << "Single2Hungry inst id is " << Single2Hungry::GetInstance();
}

void test_single2hungry() {
  LOG(INFO) << "s1 addr is " << Single2Hungry::GetInstance();
  LOG(INFO) << "s2 addr is " << Single2Hungry::GetInstance();
  for (int i = 0; i < 3; ++i) {
    std::thread tid(thread_func_single2hungry, i);
    tid.join();
  }
}

class SinglePointer {
 private:
  static SinglePointer* single;
  static std::mutex s_mutex;
 private:
  SinglePointer(){}
  SinglePointer(const SinglePointer&) = delete;
  SinglePointer& operator=(const SinglePointer&) = delete;
 public:
  static SinglePointer* GetInstance() {
    if (single != nullptr) {
      return single;
    }
    s_mutex.lock();
    if (single != nullptr) {
      s_mutex.unlock();
      return single;
    }
    single = new SinglePointer();
    s_mutex.unlock();
    return single;
  }
};
SinglePointer* SinglePointer::single = nullptr;
std::mutex SinglePointer::s_mutex;

void thread_func_lazy(int i) {
  LOG(INFO) << "this is lazy thread " << i;
  LOG(INFO) <<  "SinglePointer instance id is " << SinglePointer::GetInstance();
}

void test_singlelazy() {
  for (int i = 0; i < 3; ++i) {
    std::thread tid(thread_func_lazy, i);
    tid.join();
  }
}

class SingleAuto {
 private:
  static std::shared_ptr<SingleAuto> single;
  static std::mutex s_mutex;
 private:
  SingleAuto(){}
  SingleAuto(const SingleAuto&) = delete;
  SingleAuto& operator=(const SingleAuto&) = delete;
 public:
  ~SingleAuto() {
    LOG(INFO) << "single auto delete success ";
  }
  static std::shared_ptr<SingleAuto> GetInstance() {
    if (single != nullptr) {
      return single;
    }
    s_mutex.lock();
    if (single != nullptr) {
      s_mutex.unlock();
      return single;
    }
    single = std::shared_ptr<SingleAuto> (new SingleAuto);
    s_mutex.unlock();
    return single;
  }
};
std::shared_ptr<SingleAuto> SingleAuto::single = nullptr;
std::mutex SingleAuto::s_mutex;

void test_singleauto( ) {
  auto sp1 = SingleAuto::GetInstance();
  auto sp2 = SingleAuto::GetInstance();
  LOG(INFO) << "SingleAuto sp1  is  " << sp1;
  LOG(INFO) << "SingleAuto sp2  is  " << sp1;
}

class SingleAutoSafe;
class SafeDeletor {
 public:
  void operator()(SingleAutoSafe* sf) {
    LOG(INFO) << "this is safe deleter operator()";
    delete sf;
  }
};

class SingleAutoSafe {
 private:
  SingleAutoSafe(){}
  ~SingleAutoSafe() {
    LOG(INFO) <<  "this is single auto safe deletor";
  }
  SingleAutoSafe(const SingleAutoSafe&) = delete;
  SingleAutoSafe& operator=(const SingleAutoSafe&) = delete;
 private:
  static std::shared_ptr<SingleAutoSafe> single;
  static std::mutex s_mutex;
 public:
  static std::shared_ptr<SingleAutoSafe> GetInstance() {
    if (single != nullptr) {
      return single;
    }
    s_mutex.lock();
    if (single != nullptr) {
      s_mutex.unlock();
      return single;
    }
    single = std::shared_ptr<SingleAutoSafe>(new SingleAutoSafe, SafeDeletor());
    s_mutex.unlock();
    return single;
  }
};

class SingleTonOnce {
 private:
  SingleTonOnce() = default;
  SingleTonOnce(const SingleTonOnce&) = delete;
  SingleTonOnce& operator=(const SingleTonOnce& st) = delete;
  static std::shared_ptr<SingleTonOnce> _instance;
 public:
  static std::shared_ptr<SingleTonOnce> GetInstance() {
    static std::once_flag s_flag;
    std::call_once(s_flag, [&]() {
      _instance = std::shared_ptr<SingleTonOnce>(new SingleTonOnce);
    });
    return _instance;
  }

  void PrintAddress() {
    LOG(INFO) << _instance.get();
  }

  ~SingleTonOnce() {
    LOG(INFO) << "this is singleton destruct";
  }
};
std::shared_ptr<SingleTonOnce> SingleTonOnce::_instance = nullptr;

void TestSingle() {
  std::thread t1([]() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    SingleTonOnce::GetInstance()->PrintAddress();
  });

  std::thread t2([]() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    SingleTonOnce::GetInstance()->PrintAddress();
  });
  t1.join();
  t2.join();
}

template<typename T>
class SingleTon {
 protected:
  SingleTon() = default;
  SingleTon(const SingleTon<T>&) = delete;
  SingleTon& operator=(const SingleTon<T>& st) = delete;
  static std::shared_ptr<T> _instance;
 public:
  static std::shared_ptr<T> GetInstance() {
    static std::once_flag s_flag;
    std::call_once(s_flag,[&](){
      _instance = std::shared_ptr<T>(new T);
    });
    return _instance;
  }

  void PrintAddress() {
    LOG(INFO) << _instance.get();
  }
  ~SingleTon() {
    LOG(INFO) << "this is singleton destruct";
  }
};
template<typename T>
std::shared_ptr<T> SingleTon<T>::_instance = nullptr;

class Example : SingleTon<Example> {
  friend class SingleTon<Example>;
 public:
  ~Example(){}
 private:
  Example(){}
};

int main(int argc, char** argv) {
  FLAGS_alsologtostderr =1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging(argv[0]);

  test_single2hungry();
  test_singleauto();
  TestSingle();
}







