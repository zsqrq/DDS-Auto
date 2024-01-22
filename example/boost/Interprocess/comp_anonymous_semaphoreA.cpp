//
// Created by wz on 24-1-22.
//
#include "doc_anonymous_semaphore_shared_data.h"
#include "boost/interprocess/shared_memory_object.hpp"
#include "boost/interprocess/mapped_region.hpp"
#include "glog/logging.h"
#include <iostream>

int main() {
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging("Shared_SemaphoreA");

  struct shm_remove
  {
    shm_remove() {
      boost::interprocess::shared_memory_object::remove("MySharedMemorySemaphoreA");
    }
    ~shm_remove(){
      boost::interprocess::shared_memory_object::remove("MySharedMemorySemaphoreA");
    }
  } remover;
  //<-
  (void)remover;
  //->

  boost::interprocess::shared_memory_object shm (
      boost::interprocess::create_only,
      "MySharedMemorySemaphoreA",
      boost::interprocess::read_write);

  shm.truncate(sizeof(shared_memory_buffer));
  boost::interprocess::mapped_region region(shm,
                                          boost::interprocess::read_write);
  auto addr = region.get_address();
  auto data = new (addr) shared_memory_buffer;
  const int NumMsg = 100;

  for (int i = 0; i < NumMsg; ++i) {
    data->nempty.wait();
    data->mutex.wait();
    data->items[i%shared_memory_buffer::NumItems] = i;
    LOG(INFO) << "Semaphore A insert data in the array : " << i;
    data->mutex.post();
    data->nstored.post();
  }
  return 0;
}