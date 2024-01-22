//
// Created by wz on 24-1-22.
//
#include "boost/date_time.hpp"
#include "boost/thread.hpp"
#include "upgradable_mutex_shared_data.h"
#include "boost/interprocess/mapped_region.hpp"
#include "boost/interprocess/shared_memory_object.hpp"
#include "boost/interprocess/sync/scoped_lock.hpp"
#include "glog/logging.h"
#include <iostream>
#include <cstdio>

int main() {
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging("Upgradable_MutexB");

  struct shm_remove
  {
    ~shm_remove(){
      boost::interprocess::shared_memory_object::remove("UpgradableMutexA");
    }
  } remover;
  //<-
  (void)remover;
  //->

  boost::interprocess::shared_memory_object shm(boost::interprocess::open_or_create,
                                                "UpgradableMutexA",
                                                boost::interprocess::read_write);

  boost::interprocess::mapped_region region(shm,
                                            boost::interprocess::read_write);

  auto addr = region.get_address();
  auto data = static_cast<shared_data*>(addr);

  //Write some logs
  for(int i = 0; i < 100; ++i){
    //Lock the upgradable_mutex
    boost::interprocess::scoped_lock<boost::interprocess::interprocess_upgradable_mutex> lock(data->upgradable_mutex);
    std::sprintf(data->items[(data->current_line++) % shared_data::NumItems]
        ,"%s_%d", "process_b", i);
    LOG(INFO) << "Upgradable_Mutex_B print data : " << data->items[i];
    if(i == (shared_data::NumItems-1))
      data->end_b = true;
    //Mutex is released here
    boost::this_thread::sleep(boost::posix_time::milliseconds(200));
  }

  while (true) {
    boost::interprocess::scoped_lock<boost::interprocess::interprocess_upgradable_mutex> lock(data->upgradable_mutex);
    if (data->end_a) break;
  }
  return 0;
}