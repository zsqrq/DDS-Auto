//
// Created by wz on 24-1-25.
//
#include "boost/interprocess/managed_shared_memory.hpp"
#include "boost/move/utility_core.hpp"
#include "test/get_process_id_name.h"
#include "glog/logging.h"
#include <cassert>//assert
#include <cstring>//std::memset
#include <new>    //std::nothrow
#include <vector> //std::vector

using namespace boost::interprocess;

int main(int argc, char *argv[]) {
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging(argv[0]);

  typedef managed_shared_memory::multiallocation_chain multiallocation_chain;
  struct shm_remove
  {
    //<-
#if 1
    shm_remove() { shared_memory_object::remove(test::get_process_id_name()); }
    ~shm_remove(){ shared_memory_object::remove(test::get_process_id_name()); }
#else
    //->
      shm_remove() { shared_memory_object::remove("MySharedMemory"); }
      ~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
   //<-
#endif
    //->
  } remover;
  //<-
  (void)remover;
#if 1
  managed_shared_memory managed_shm(create_only,test::get_process_id_name(), 65536);
#else
  //->
   managed_shared_memory managed_shm(create_only,"MySharedMemory", 65536);
   //<-
#endif
  //Allocate 16 elements of 100 bytes in a single call. Non-throwing version.
  multiallocation_chain chain;
  managed_shm.allocate_many(std::nothrow, 100, 16, chain);
  if (chain.empty()) {
    LOG(ERROR) << "Allocate memory error";
    return 1;
  }
  std::vector<void*> allocated_buffers;

  // Initialize our data
  while (!chain.empty()) {
    void* buf = chain.pop_front();
    allocated_buffers.push_back(buf);
    std::memset(buf, 0 , 100);
  }

  //Now deallocate
  while (!allocated_buffers.empty()) {
    managed_shm.deallocate(allocated_buffers.back());
    allocated_buffers.pop_back();
  }

  //Allocate 10 buffers of different sizes in a single call. Throwing version
  managed_shared_memory::size_type sizes[10];
  for(std::size_t i = 0; i < 10; ++i)
    sizes[i] = i*3;

  managed_shm.allocate_many(sizes, 10, 1, chain);
  managed_shm.deallocate_many(chain);

  return 0;
}