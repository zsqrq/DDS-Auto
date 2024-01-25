//
// Created by wz on 24-1-25.
//
#include "boost/interprocess/detail/workaround.hpp"
#include "boost/interprocess/containers/list.hpp"
#include "boost/interprocess/managed_heap_memory.hpp"
#include "boost/interprocess/allocators/allocator.hpp"
#include "glog/logging.h"
#include <cstddef>

using namespace boost::interprocess;
using MyList =
    boost::interprocess::list<int,
                              allocator<int, managed_heap_memory::segment_manager>>;

int main(int argc, char *argv[]) {
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging(argv[0]);

  //We will create a buffer of 1000 bytes to store a list
  managed_heap_memory heap_memory(1000);
  MyList *mylist = heap_memory.construct<MyList>("MyList")(heap_memory.get_segment_manager());

  //Obtain handle, that identifies the list in the buffer
  managed_heap_memory::handle_t list_handle = heap_memory.get_handle_from_address(mylist);

  BOOST_TRY {
      while (true) {
        mylist->insert(mylist->begin(), 1);
      }
    } BOOST_CATCH(const bad_alloc&) {

  }BOOST_CATCH_END
  // Obtain the size of the list
  MyList::size_type old_size = mylist->size();
  LOG(INFO) << "Init list size is : "<< (int)old_size;
  (void)old_size;
  //To make the list bigger, let's increase the heap buffer
  //in 1000 bytes more.
  heap_memory.grow(1000);

  //If memory has been reallocated, the old pointer is invalid, so
  //use previously obtained handle to find the new pointer.
  mylist = static_cast<MyList*>(heap_memory.get_address_from_handle(list_handle));

  //Fill list until there is no more memory in the buffer
  BOOST_TRY {
      while (true) {
        mylist->insert(mylist->begin(), 1);
      }
  }BOOST_CATCH(const bad_alloc &){
  }BOOST_CATCH_END

  //Let's obtain the new size of the list
  MyList::size_type new_size = mylist->size();
  (void)new_size;
  LOG(INFO) << "New list size is : "<< (int)new_size;

  assert(new_size > old_size);

  heap_memory.destroy_ptr(mylist);

  return 0;
}