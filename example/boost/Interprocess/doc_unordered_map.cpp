//
// Created by wz on 24-1-26.
//
#include "boost/interprocess/detail/workaround.hpp"
#include "boost/interprocess/managed_shared_memory.hpp"
#include "boost/interprocess/allocators/allocator.hpp"
#include "boost/interprocess/detail/config_external_begin.hpp"
#include "boost/unordered_map.hpp"
#include "boost/interprocess/detail/config_external_end.hpp"
#include "test/get_process_id_name.h"
#include "boost/container_hash/hash.hpp"
#include <functional>

#include "glog/logging.h"

using namespace boost::interprocess;

int main(int argc, char *argv[]) {
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging(argv[0]);

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
  managed_shared_memory segment(create_only, test::get_process_id_name(), 65536);
#else
  //->
   managed_shared_memory segment(create_only, "MySharedMemory", 65536);
   //<-
#endif

  using KeyType = int;
  using MappedType = float;
  using ValueType = std::pair<const int, float>;

  // Define the allocator
  using ShmemAllocator = allocator<ValueType, managed_shared_memory::segment_manager>;
  using MyHashMap = boost::unordered_map<KeyType, MappedType,
                                         boost::hash<KeyType>, std::equal_to<KeyType>, ShmemAllocator>;

  MyHashMap * myhashmap = segment.construct<MyHashMap>("MyHashMap")
      (3u, boost::hash<int>(), std::equal_to<int>(), segment.get_allocator<ValueType>());
  for (std::size_t i = 0; i < 100u; ++i) {
    myhashmap->insert(ValueType((int)i, (float )i));
  }

  return 0;
}