//
// Created by wz on 23-12-28.
//
#include <iostream>
#include <mutex>
#include <thread>
#include <map>
#include <shared_mutex>

#include "glog/logging.h"

std::mutex mtx;
int shared_data = 0;

void use_unique() {
  std::unique_lock<std::mutex> lck(mtx);
  LOG(INFO) << "lock success";
  shared_data++;
  lck.unlock();
}

void owns_lock() {
  std::unique_lock<std::mutex> lock(mtx);
  shared_data++;
  if (lock.owns_lock()) {
    LOG(INFO) << "owns lock";
  } else {
    LOG(WARNING) << "doesn't own lock";
  }
  lock.unlock();
  if (lock.owns_lock()) {
    LOG(INFO) << "owns lock";
  } else {
    LOG(WARNING) << "doesn't own lock";
  }
}

void defer_lock() {
  std::unique_lock<std::mutex> lock(mtx, std::defer_lock);
  lock.lock();
  LOG(INFO) << "defer lock locked";
  lock.unlock();
  LOG(INFO) << "defer lock unlocked";
}

void use_own_defer() {
  std::unique_lock<std::mutex> lock(mtx);

  if (lock.owns_lock()) {
    LOG(INFO) << "Main thread has the lock.";
  } else {
    LOG(WARNING) << "Main thread does not have the lock.";
  }

  std::thread t([]() {
    std::unique_lock<std::mutex> lock(mtx,std::defer_lock);
    if (lock.owns_lock()) {
      LOG(INFO) << "Thread has the lock.";
    } else {
      LOG(WARNING) << "Thread does not have the lock.";
    }

    lock.lock();
    if (lock.owns_lock()) {
      LOG(INFO) << "Thread has the lock.";
    } else {
      LOG(WARNING) << "Thread does not have the lock.";
    }
    lock.unlock();
  });
  t.join();
}

void use_own_adopt() {
  mtx.lock();
  std::unique_lock<std::mutex> lock(mtx, std::adopt_lock);
  if (lock.owns_lock()) {
    LOG(INFO) << "owns lock" ;
  }
  else {
    LOG(WARNING) << "does not have the lock" ;
  }
  lock.unlock();
}

int a = 10;
int b = 99;
std::mutex  mtx1;
std::mutex  mtx2;

void safe_swap() {
  std::lock(mtx1, mtx2);
  std::unique_lock<std::mutex> lock1(mtx1, std::adopt_lock);
  std::unique_lock<std::mutex> lock2(mtx2, std::adopt_lock);
  std::swap(a,b);
}

void safe_swap2() {
  std::unique_lock<std::mutex> lock1(mtx1, std::defer_lock);
  std::unique_lock<std::mutex> lock2(mtx2, std::defer_lock);
  std::lock(lock1, lock2);
  std::swap(a, b);
}

std::unique_lock <std::mutex>  get_lock() {
  std::unique_lock<std::mutex>  lock(mtx);
  shared_data++;
  return lock;
}

void use_return() {
  std::unique_lock<std::mutex> lock(get_lock());
  shared_data++;
}

void precision_lock( ) {
  std::unique_lock<std::mutex> lock(mtx);
  shared_data++;
  lock.unlock();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  lock.lock();
  shared_data++;
}

class DNService {
 private:
  std::map<std::string, std::string> _dns_info;
  mutable std::shared_mutex _shared_mtx;
 public:
  DNService() {}
  std::string QueryDNS(std::string dnsname) {
    std::shared_lock<std::shared_mutex> shared_lock(_shared_mtx);
    auto iter = _dns_info.find(dnsname);
    if (iter != _dns_info.end()) {
      return iter->second;
    }
    return "";
  }

  void AddDnsInfo(std::string dnsname, std::string dnsentry) {
    std::lock_guard<std::shared_mutex> guard_locks(_shared_mtx);
    _dns_info.insert(std::make_pair(dnsname, dnsentry));
  }
};

class RecursiveDemo {
 private:
  std::map<std::string, int> _students_info;
  std::recursive_mutex _recursive_mtx;
 public:
  RecursiveDemo() {}

  bool QueryStudent(std::string name) {
    std::lock_guard<std::recursive_mutex> recursive_lock(_recursive_mtx);
    auto iter_find = _students_info.find(name);
    if (iter_find == _students_info.end()) {
      return false;
    }
    return true;
  }

  void AddScore(std::string name, int score) {
    std::lock_guard<std::recursive_mutex> recursive_lock(_recursive_mtx);
    if (!QueryStudent(name)) {
      _students_info.insert(std::make_pair(name, score));
      return;
    }
    _students_info[name] = _students_info[name] +score;
  }

  void AddScoreAtomic(std::string name, int score) {
    std::lock_guard<std::recursive_mutex>  recursive_lock(_recursive_mtx);
    auto iter_find = _students_info.find(name);
    if (iter_find == _students_info.end()) {
      _students_info.insert(std::make_pair(name, score));
      return;
    }

    _students_info[name] = _students_info[name] + score;
    return;
  }
};

int main(int argc, char** argv) {
  FLAGS_minloglevel = 0;
  FLAGS_alsologtostderr =1;
  google::InitGoogleLogging(argv[0]);

  use_unique();
  owns_lock();
  defer_lock();
  use_unique();
  use_own_defer();
  use_own_adopt();
  safe_swap();
  safe_swap2();
  use_return();

  return 0;
}