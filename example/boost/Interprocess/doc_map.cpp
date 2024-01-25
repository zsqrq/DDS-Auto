//
// Created by wz on 24-1-25.
//
#include "boost/interprocess/detail/workaround.hpp"
#include "boost/interprocess/managed_shared_memory.hpp"
#include "boost/interprocess/containers/map.hpp"
#include "boost/interprocess/allocators/allocator.hpp"
#include "test/get_process_id_name.h"
#include "glog/logging.h"

#include <functional>
#include <utility>

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

  //Shared memory front-end that is able to construct objects
  //associated with a c-string. Erase previous shared memory with the name
  //to be used and create the memory segment at the specified address and initialize resources
  //<-
#if 1
  managed_shared_memory segment(create_only,test::get_process_id_name(), 65536);
#else
  //->
   managed_shared_memory segment
      (create_only
      ,"MySharedMemory" //segment name
      ,65536);          //segment size in bytes
   //<-
#endif
  //->

  //Note that map<Key, MappedType>'s value_type is std::pair<const Key, MappedType>,
  //so the allocator must allocate that pair.
  typedef int    KeyType;
  typedef float  MappedType;
  typedef std::pair<const int, float> ValueType;
  //Alias an STL compatible allocator of for the map.
  //This allocator will allow to place containers
  //in managed shared memory segments
  typedef allocator<ValueType, managed_shared_memory::segment_manager> ShmemAllocator;

  typedef boost::interprocess::map<KeyType, MappedType,std::less<KeyType>, ShmemAllocator> MyMap;

  ShmemAllocator alloc_inst (segment.get_segment_manager());
  MyMap *mymap = segment.construct<MyMap>("MyMap")(std::less<int>(), alloc_inst);

  for (int i = 0; i < 100; ++i) {
    mymap->insert(std::pair<const int, float>(i, (float )i));
  }

  return 0;
}