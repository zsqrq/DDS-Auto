//
// Created by wz on 24-1-22.
//
#include "test/get_process_id_name.h"
#include "boost/interprocess/detail/workaround.hpp"
#include "boost/interprocess/managed_shared_memory.hpp"
#include "boost/interprocess/allocators/adaptive_pool.hpp"
#include "glog/logging.h"
#include <cassert>

int main() {
  struct shm_remove {
  #if 1
    shm_remove() {
      boost::interprocess::shared_memory_object::remove(boost::interprocess::test::get_process_id_name());
    }
    ~shm_remove() {
      boost::interprocess::shared_memory_object::remove(boost::interprocess::test::get_process_id_name());
    }
  #else
    shm_remove() {
      boost::interprocess::shared_memory_object::remove("MySharedMemory");
    }
    ~shm_remove() {
      boost::interprocess::shared_memory_object::remove("MySharedMemory");
    }
  #endif
  } remover;
  (void)remover;
}
