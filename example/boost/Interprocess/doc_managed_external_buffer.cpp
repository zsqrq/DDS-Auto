//
// Created by wz on 24-1-25.
//
#include "boost/interprocess/managed_external_buffer.hpp"
#include "boost/interprocess/allocators/allocator.hpp"
#include "boost/interprocess/containers/list.hpp"
#include "boost/aligned_storage.hpp"
#include "glog/logging.h"
#include <cstring>


using namespace boost::interprocess;

int main(int argc, char *argv[]) {
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging(argv[0]);

  //Create the static memory who will store all objects
  const int memsize = 65536;
  static boost::aligned_storage<memsize>::type static_buffer;

  //This managed memory will construct objects associated with
  //a wide string in the static buffer
  wmanaged_external_buffer objects_in_static_memory(create_only,&static_buffer,memsize);

  //We optimize resources to create 100 named objects in the static buffer
  objects_in_static_memory.reserve_named_objects(100);

  using allocator_t = allocator<int, wmanaged_external_buffer::segment_manager>;
  using MyBufferList = list<int, allocator_t>;

  //The list must be initialized with the allocator
  //All objects created with objects_in_static_memory will
  //be stored in the static_buffer!
  MyBufferList *list = objects_in_static_memory.construct<MyBufferList>(L"MyList")
      (objects_in_static_memory.get_segment_manager());
  (void)list;

  static boost::aligned_storage<memsize>::type static_buffer2;
  std::memcpy(&static_buffer2, &static_buffer, memsize);

  //Now open the duplicated managed memory passing the memory as argument
  wmanaged_external_buffer objects_in_static_memory2
      (open_only, &static_buffer2, memsize);

  if (!objects_in_static_memory2.find<MyBufferList>(L"MyList").first)
    return 1;

  //Destroy the lists from the static buffers
  objects_in_static_memory.destroy<MyBufferList>(L"MyList");
  objects_in_static_memory2.destroy<MyBufferList>(L"MyList");
  return 0;
}