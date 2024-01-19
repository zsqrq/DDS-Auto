//
// Created by wz on 24-1-19.
//
#include "boost/date_time.hpp"
#include "boost/thread.hpp"
#include "boost/interprocess/shared_memory_object.hpp"
#include "boost/interprocess/mapped_region.hpp"
#include "boost/interprocess/sync/scoped_lock.hpp"
#include "doc_anonymous_mutex_shared_data.h"
#include "glog/logging.h"

int main() {
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging("intra_mutexB");

  struct shm_remove
  {
    ~shm_remove(){
      boost::interprocess::shared_memory_object::remove("MyMutexSharedMemory");
    }
  } remover;
  (void) remover;
  boost::interprocess::shared_memory_object shm(boost::interprocess::open_only,
                                                "MyMutexSharedMemory",
                                                boost::interprocess::read_write);
  boost::interprocess::mapped_region region(shm,
                                            boost::interprocess::read_write);
  auto addr = region.get_address();
  auto data = static_cast<shared_memory_log*>(addr);
  int counter = 0;

  for(int i = 0; i < 100; ++i){
    //Lock the mutex
    boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(data->mutex);
    std::sprintf(data->items[(data->current_line++) % shared_memory_log::NumItems]
        ,"%s_%d", "process_b", counter++);
    LOG(INFO) << "Process B published Message : " << data->items[i];
    if(i == (shared_memory_log::NumItems-1))
      data->end_b = true;
    //Mutex is released here
    boost::this_thread::sleep(boost::posix_time::milliseconds(200));

  }
  while (true) {
    boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(data->mutex);
    if (data->end_a) break;
  }
  return 0;
}