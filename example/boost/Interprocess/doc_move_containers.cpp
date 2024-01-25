//
// Created by wz on 24-1-25.
//
#include "boost/interprocess/detail/workaround.hpp"
#include "boost/interprocess/managed_shared_memory.hpp"
#include "boost/interprocess/containers/vector.hpp"
#include "boost/interprocess/containers/string.hpp"
#include "boost/interprocess/allocators/allocator.hpp"
#include "test/get_process_id_name.h"
#include "glog/logging.h"

#include <cassert>

using namespace boost::interprocess;

int main(int argc, char *argv[]) {
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging(argv[0]);

  //Typedefs
  typedef managed_shared_memory::segment_manager     SegmentManager;
  typedef allocator<char, SegmentManager>            CharAllocator;
  typedef basic_string<char, std::char_traits<char>
      ,CharAllocator>                MyShmString;
  typedef allocator<MyShmString, SegmentManager>     StringAllocator;
  typedef vector<MyShmString, StringAllocator>       MyShmStringVector;

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

  //<-
#if 1
  managed_shared_memory shm(create_only, test::get_process_id_name(), 65536);
#else
  //->
   managed_shared_memory shm(create_only, "MySharedMemory", 10000);
   //<-
#endif
  //->

  CharAllocator charallocator (shm.get_segment_manager());
  StringAllocator stringallocator (shm.get_segment_manager());

  //Create a vector of strings in shared memory.
  MyShmStringVector* myshmvector = shm.construct<MyShmStringVector>("myshmvector")(stringallocator);

  //Insert 50 strings in shared memory. The strings will be allocated
  //only once and no string copy-constructor will be called when inserting
  //strings, leading to a great performance.
  MyShmString string_to_compare(charallocator);
  string_to_compare = "this is a long, long, long, long, long, long, string...";
  myshmvector->reserve(50);

  for (int i = 0; i < 50; ++i) {
    MyShmString move_me(string_to_compare);
    myshmvector->push_back(boost::move(move_me));
    //The source string is in default constructed state
    assert(move_me.empty());
    //The newly created string will be equal to the "move_me"'s old contents
    assert(myshmvector->back() == string_to_compare);
  }

  myshmvector->pop_back();
  myshmvector->insert(myshmvector->begin(),boost::move(string_to_compare));

  shm.destroy_ptr(myshmvector);
  return 0;
}