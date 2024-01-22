//
// Created by wz on 24-1-22.
//
#include "boost/date_time.hpp"
#include "boost/thread.hpp"
#include "upgradable_mutex_shared_data.h"
#include "boost/interprocess/shared_memory_object.hpp"
#include "boost/interprocess/mapped_region.hpp"
#include "boost/interprocess/sync/scoped_lock.hpp"
#include "glog/logging.h"

#include <iostream>
#include <cstdio>

int main() {
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging("Upgradable_MutexA");

  struct shm_remove {
    ~shm_remove() {
      boost::interprocess::shared_memory_object::remove("UpgradableMutexA");
    }
  } remover;
  (void)remover;

  boost::interprocess::shared_memory_object shm(boost::interprocess::open_or_create,
                                                "UpgradableMutexA",
                                                boost::interprocess::read_write);
  shm.truncate(sizeof(shared_data));
  boost::interprocess::mapped_region region(shm,
                                            boost::interprocess::read_write);

  auto addr = region.get_address();
  auto data = new (addr) shared_data;

  for (int i = 0; i < shared_data::NumItems; ++i) {
    boost::interprocess::scoped_lock<boost::interprocess::interprocess_upgradable_mutex> lock(data->upgradable_mutex);
    std::sprintf(data->items[(data->current_line++) % shared_data::NumItems]
        ,"%s_%d", "process_a", i);
    LOG(INFO) << "Upgradable_Mutex_A print data : " << data->items[i];
    if (i == (shared_data::NumItems - 1)) {
      data->end_a = true;
    }
    boost::this_thread::sleep(boost::posix_time::milliseconds(200));
  }

  while(1){
    boost::interprocess::scoped_lock<boost::interprocess::interprocess_upgradable_mutex> lock(data->upgradable_mutex);
    if(data->end_b)
      break;
  }

  return 0;
}