//
// Created by wz on 24-1-26.
//
#include "boost/interprocess/detail/workaround.hpp"
#include "boost/interprocess/managed_shared_memory.hpp"
#include "boost/interprocess/allocators/node_allocator.hpp"
#include "test/get_process_id_name.h"
#include "glog/logging.h"
#include <cassert>

using namespace boost::interprocess;

int main(int argc, char *argv[]) {
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging(argv[0]);

  //Remove shared memory on construction and destruction
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
  //->

  //Create shared memory
  //<-
#if 1
  managed_shared_memory segment(create_only,
                                test::get_process_id_name(),  //segment name
                                65536);
#else
  //->
   managed_shared_memory segment(create_only,
                                 "MySharedMemory",  //segment name
                                 65536);
   //<-
#endif

  using node_allocator_t = boost::interprocess::node_allocator<int,
      managed_shared_memory::segment_manager>;

  node_allocator_t allocator_instance(segment.get_segment_manager());
  node_allocator_t allocator_instance2(segment.get_segment_manager());
  node_allocator_t allocator_instance3(allocator_instance2);

  assert(allocator_instance == allocator_instance2);
  assert(allocator_instance2 == allocator_instance3);

  allocator_instance2.deallocate(allocator_instance.allocate(1), 1);
  allocator_instance3.deallocate(allocator_instance2.allocate(1),1);
  return 0;
}