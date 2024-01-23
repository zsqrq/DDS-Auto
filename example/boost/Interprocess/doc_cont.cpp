//
// Created by wz on 24-1-23.
//
#include "boost/interprocess/detail/workaround.hpp"
#include "boost/interprocess/containers/vector.hpp"
#include "boost/interprocess/allocators/allocator.hpp"
#include "boost/interprocess/managed_shared_memory.hpp"
#include "test/get_process_id_name.h"

int main() {
  using namespace boost::interprocess;
  struct shm_remove {
    shm_remove() {
      shared_memory_object::remove("MySharedMemory");
    }
    ~shm_remove() {
      shared_memory_object::remove("MySharedMemory");
    }
  } remover;
  (void)remover;

  managed_shared_memory segment(create_only,"MySharedMemory",65536);

  using ShmemAllocator = allocator<int, managed_shared_memory::segment_manager>;
  using MyVector = vector<int, ShmemAllocator>;

  int initVal[] = {0, 1, 2, 3, 4, 5, 6};
  const int *begVal = initVal;
  const int *endVal = initVal + sizeof(initVal) / sizeof(initVal[0]);

  const ShmemAllocator alloc_inst(segment.get_segment_manager());

  MyVector *myvector = segment.construct<MyVector>("MyVector")(
      begVal, endVal, alloc_inst);
  std::sort(myvector->rbegin(), myvector->rend());

  segment.destroy<MyVector>("MyVector");
  return 0;
}