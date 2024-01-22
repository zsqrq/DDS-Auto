//
// Created by wz on 24-1-22.
//
#include "glog/logging.h"
#include "boost/interprocess/detail/workaround.hpp"
#include "boost/interprocess/managed_shared_memory.hpp"
#include "boost/interprocess/allocators/allocator.hpp"
#include <cassert>
#include "test/get_process_id_name.h"

int main() {
  FLAGS_minloglevel = 0;
  FLAGS_alsologtostderr = 1;
  google::InitGoogleLogging("DocAllocator");

  struct shm_remove {
    shm_remove() {
      boost::interprocess::shared_memory_object::remove(boost::interprocess::test::get_process_id_name());
    }
    ~shm_remove() {
      boost::interprocess::shared_memory_object::remove(boost::interprocess::test::get_process_id_name());
    }
  } remover;
  (void)remover;
  boost::interprocess::managed_shared_memory segment(boost::interprocess::create_only,
                                                     boost::interprocess::test::get_process_id_name(),
                                                     65536);
  boost::interprocess::allocator<int, boost::interprocess::managed_shared_memory::segment_manager>
      allocator_instance(segment.get_segment_manager());
  boost::interprocess::allocator<int, boost::interprocess::managed_shared_memory::segment_manager>
      allocator_instance2(allocator_instance);
  allocator_instance2.deallocate(allocator_instance.allocate(100),100);
  return 0;
}