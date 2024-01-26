//
// Created by wz on 24-1-26.
//

#include <boost/interprocess/detail/workaround.hpp>
//[doc_offset_ptr
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/offset_ptr.hpp>
#include "test/get_process_id_name.h"
#include "glog/logging.h"

using namespace boost::interprocess;

struct list_node {
  boost::interprocess::offset_ptr<list_node> next;
  int value;
};

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

  //Create shared memory
  //<-
#if 1
  managed_shared_memory segment(create_only,
                                test::get_process_id_name(),  //segment name
                                65536);
#else
  //->
   managed_shared_memory segment(create_only,
                                 "MySharedMemory",  //segment name
                                 65536);
   //<-
#endif
  //Create linked list with 10 nodes in shared memory
  offset_ptr<list_node> prev = 0, current, first;
  int i;
  for (int i = 0; i < 10; ++i, prev = current) {
    current = static_cast<list_node*>(segment.allocate(sizeof(list_node)));
    current->value = i;
    current->next = 0;
    if (!prev) {
      first = current;
    } else {
      prev->next = current;
    }
  }
  //When done, destroy list
  for (current = first; current;) {
    prev = current;
    current = current->next;
    segment.deallocate(prev.get());
  }

  return 0;
}