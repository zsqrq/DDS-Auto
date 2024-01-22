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
  google::InitGoogleLogging("Shared_SemaphoreB");

  struct shm_remove
  {
    ~shm_remove()
    {
      boost::interprocess::shared_memory_object::remove("MySharedMemorySemaphoreA");
    }
  } remover;
  //<-
  (void)remover;
  //->

  boost::interprocess::shared_memory_object shm(boost::interprocess::open_only,
                                                "MySharedMemorySemaphoreA",
                                                boost::interprocess::read_write);

  boost::interprocess::mapped_region region(shm,boost::interprocess::read_write);

  auto addr = region.get_address();
  auto data = static_cast<shared_memory_buffer*>(addr);

  const int NumMsg = 100;
  int extracted_data[NumMsg];
  (void)extracted_data;

  for(int i = 0; i < NumMsg; ++i){
    data->nstored.wait();
    data->mutex.wait();
    extracted_data[i] = data->items[i % shared_memory_buffer::NumItems];
    LOG(INFO) << "Semaphore B extracted data in the array : " << extracted_data[i];
    data->mutex.post();
    data->nempty.post();
  }

  return 0;
}