//
// Created by wz on 24-1-25.
//

#include "boost/interprocess/managed_shared_memory.hpp"
#include "test/get_process_id_name.h"
#include "glog/logging.h"

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

  //Managed memory segment that allocates portions of a shared memory
  //segment with the default management algorithm
  //<-
#if 1
  managed_shared_memory managed_shm(create_only,test::get_process_id_name(), 65536);
#else
  //->
   managed_shared_memory managed_shm(create_only,"MySharedMemory", 65536);
   //<-
#endif
  //->

  //Allocate 100 bytes of memory from segment, throwing version
  void *ptr = managed_shm.allocate(100);

  //Deallocate it
  managed_shm.deallocate(ptr);

  //Non throwing version
  ptr = managed_shm.allocate(100, std::nothrow);

  //Deallocate it
  managed_shm.deallocate(ptr);
  return 0;
}