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
  FLAGS_minloglevel = 0;
  FLAGS_alsologtostderr = 1;
  google::InitGoogleLogging("AdaptivePool");
  struct shm_remove {
  #if 1
    shm_remove() {
      boost::interprocess::shared_memory_object::remove(boost::interprocess::test::get_process_id_name());
      LOG(INFO) << "Allocate memory : " << boost::interprocess::test::get_process_id_name();
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

  //Create shared memory
  #if 1
  boost::interprocess::managed_shared_memory segment(boost::interprocess::create_only,
                                                         boost::interprocess::test::get_process_id_name(),
                                                         65536);
  #else
  boost::interprocess::managed_shared_memory segment(boost::interprocess::create_only,
                                                     "MySharedMemory",
                                                     65536);
  #endif
  //Create a adaptive_pool that allocates ints from the managed segment
  //The number of chunks per segment is the default value
  using adaptive_pool_t =
      boost::interprocess::adaptive_pool<int,
          boost::interprocess::managed_shared_memory::segment_manager>;
  adaptive_pool_t allocator_instance(segment.get_segment_manager());

  //Create another adaptive_pool. Since the segment manager address
  //is the same, this adaptive_pool will be
  //attached to the same pool so "allocator_instance2" can deallocate
  //nodes allocated by "allocator_instance"
  adaptive_pool_t allocator_instance2(segment.get_segment_manager());

  adaptive_pool_t allocator_instance3(allocator_instance2);

  assert(allocator_instance == allocator_instance2);
  assert(allocator_instance2 == allocator_instance3);
  allocator_instance2.deallocate(allocator_instance.allocate(1),1);
  allocator_instance3.deallocate(allocator_instance2.allocate(1),1);
  return 0;
}
