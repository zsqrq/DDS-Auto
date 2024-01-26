//
// Created by wz on 24-1-26.
//
#include <boost/interprocess/detail/workaround.hpp>
//[doc_spawn_vector
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <string>
#include <cstdlib> //std::system
#include "test/get_process_id_name.h"
#include "glog/logging.h"

using namespace boost::interprocess;

using ShmemAllocator = allocator<int, managed_shared_memory::segment_manager>;
using MyVector = vector<int, ShmemAllocator>;

int main(int argc, char *argv[]) {
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging(argv[0]);

  if(argc == 1){ //Parent process
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

    //Create a new segment with given name and size
    //<-
#if 1
    managed_shared_memory segment(create_only, test::get_process_id_name(), 65536);
#else
    //->
      managed_shared_memory segment(create_only, "MySharedMemory", 65536);
      //<-
#endif
    //->

    //Initialize shared memory STL-compatible allocator
    const ShmemAllocator alloc_inst (segment.get_segment_manager());

    //Construct a vector named "MyVector" in shared memory with argument alloc_inst
    MyVector *myvector = segment.construct<MyVector>("MyVector")(alloc_inst);

    for(int i = 0; i < 100; ++i)  //Insert data in the vector
      myvector->push_back(i);

    //Launch child process
    std::string s(argv[0]); s += " child ";
    //<-
    s += test::get_process_id_name();
    //->
    if(0 != std::system(s.c_str()))
      return 1;

    //Check child has destroyed the vector
    if(segment.find<MyVector>("MyVector").first)
      return 1;
  }
  else{ //Child process
    //Open the managed segment
    //<-
#if 1
    managed_shared_memory segment(open_only, argv[2]);
#else
    //->
      managed_shared_memory segment(open_only, "MySharedMemory");
      //<-
#endif
    //->

    //Find the vector using the c-string name
    MyVector *myvector = segment.find<MyVector>("MyVector").first;

    //Use vector in reverse order
    std::sort(myvector->rbegin(), myvector->rend(),std::greater<int>());
    for(int i = 0; i < 100; ++i)  //Insert data in the vector
      LOG(INFO) << "MyVector Has elements : " << myvector->at(i);

    //When done, destroy the vector from the segment
    segment.destroy<MyVector>("MyVector");
  }

  return 0;
}