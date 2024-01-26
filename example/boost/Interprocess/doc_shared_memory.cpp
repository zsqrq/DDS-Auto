//
// Created by wz on 24-1-26.
//
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <cstring>
#include <cstdlib>
#include <string>
#include "test/get_process_id_name.h"
#include "glog/logging.h"

using namespace boost::interprocess;

int main(int argc, char *argv[]) {
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging(argv[0]);

  if (argc == 1) {
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

    //Create a shared memory object.
    //<-
#if 1
    shared_memory_object shm (create_only, test::get_process_id_name(), read_write);
#else
    //->
      shared_memory_object shm (create_only, "MySharedMemory", read_write);
      //<-
#endif
    shm.truncate(1000);
    mapped_region region(shm, read_write);
    //Write all the memory to 1
    std::memset(region.get_address(),4,region.get_size());
    //Launch child process
    std::string s(argv[0]); s += " child ";
    //<-
    s += test::get_process_id_name();
    //->
    if(0 != std::system(s.c_str()))
      return 1;
  }
  else {
#if 1
    shared_memory_object shm (open_only, argv[2], read_only);
#else
    //->
      shared_memory_object shm (open_only, "MySharedMemory", read_only);
      //<-
#endif
    //->
    mapped_region region(shm, read_only);

    char *mem = static_cast<char*>(region.get_address());
    for(std::size_t i = 0; i < region.get_size(); ++i)
      LOG(INFO) << "Child process read data : " <<  std::to_string(*mem);
      if(*mem++ != 4)
        return 1;   //Error checking memory
  }
  return 0;
}