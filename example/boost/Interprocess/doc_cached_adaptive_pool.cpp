//
// Created by wz on 24-1-23.
//
#include "boost/interprocess/detail/workaround.hpp"
#include "boost/interprocess/allocators/cached_adaptive_pool.hpp"
#include "boost/interprocess/managed_shared_memory.hpp"
#include "glog/logging.h"
#include "test/get_process_id_name.h"
#include <cassert>

using namespace boost::interprocess;

int main(int argc, char** argv) {
  struct shm_remove {
    shm_remove() {
      shared_memory_object::remove(test::get_process_id_name());
    }
    ~shm_remove() {
      shared_memory_object::remove(test::get_process_id_name());
    }
  }remover;
  (void)remover;

  managed_shared_memory segment(create_only,test::get_process_id_name(),65536);

  typedef cached_adaptive_pool<int, managed_shared_memory::segment_manager>
      cached_adaptive_pool_t;
  cached_adaptive_pool_t allocator_instance(segment.get_segment_manager());
  //The max cached nodes are configurable per instance
  allocator_instance.set_max_cached_nodes(3);

  //Create another cached_adaptive_pool. Since the segment manager address
  //is the same, this cached_adaptive_pool will be
  //attached to the same pool so "allocator_instance2" can deallocate
  //nodes allocated by "allocator_instance"
  cached_adaptive_pool_t allocator_instace2(segment.get_segment_manager());

  allocator_instace2.set_max_cached_nodes(5);

  cached_adaptive_pool_t allocator_instace3(allocator_instace2);

  allocator_instace3.deallocate_cache();

  //All allocators are equal
  assert(allocator_instance == allocator_instace2);
  assert(allocator_instace2 == allocator_instace3);

  allocator_instace2.deallocate(allocator_instance.allocate(1),1);
  allocator_instace3.deallocate(allocator_instace2.allocate(1),1);

  return 0;
}