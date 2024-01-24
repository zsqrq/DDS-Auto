//
// Created by wz on 24-1-24.
//

#include "boost/interprocess/managed_shared_memory.hpp"
#include "test/get_process_id_name.h"
#include "glog/logging.h"
#include <cassert>
#include <cstring>

using namespace boost::interprocess;

class my_class {};

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

  managed_shared_memory managed_shm(create_only,test::get_process_id_name(),10000*sizeof(size_t));
  my_class* named_object = managed_shm.construct<my_class>("Object_Name")[1]();
  my_class* unique_object = managed_shm.construct<my_class>(unique_instance)[2]();
  my_class* anon_object = managed_shm.construct<my_class>(anonymous_instance)[3]();

  if (0 == std::strcmp(managed_shared_memory::get_instance_name(named_object), "Object_Name")) {
    LOG(INFO) << "named_object got name : " << managed_shared_memory::get_instance_name(named_object);
  }
  if (0 == std::strcmp(managed_shared_memory::get_instance_name(unique_object), typeid(my_class).name())) {
    LOG(INFO) << "unique_object got name : " << managed_shared_memory::get_instance_name(unique_object);
  }
  if (0 == managed_shared_memory::get_instance_name(anon_object)) {
    LOG(INFO) << "anon_object got name : " << "anon";
  }

  if (named_type == managed_shared_memory::get_instance_type(named_object)) {
    LOG(INFO) << "named_object got type : named_type" ;
  }
  if (unique_type == managed_shared_memory::get_instance_type(unique_object)) {
    LOG(INFO) << "unique_object got type : unique_object" ;
  }
  if (anonymous_type == managed_shared_memory::get_instance_type(anon_object)) {
    LOG(INFO) << "anon_object got type : anon_object" ;
  }

  if (1 == managed_shared_memory::get_instance_length(named_object)) {
    LOG(INFO) << "named_object got length : 1" ;
  }
  if (2 == managed_shared_memory::get_instance_length(unique_object)) {
    LOG(INFO) << "unique_object got length : 2" ;
  }
  if (3 == managed_shared_memory::get_instance_length(anon_object)) {
    LOG(INFO) << "anon_object got length : 3" ;
  }

  managed_shm.destroy_ptr(named_object);
  managed_shm.destroy_ptr(unique_object);
  managed_shm.destroy_ptr(anon_object);

  return 0;
}