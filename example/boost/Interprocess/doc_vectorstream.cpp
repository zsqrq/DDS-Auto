//
// Created by wz on 24-1-26.
//
#include "boost/interprocess/detail/workaround.hpp"
//[doc_vectorstream
#include "boost/interprocess/containers/vector.hpp"
#include "boost/interprocess/containers/string.hpp"
#include "boost/interprocess/allocators/allocator.hpp"
#include "boost/interprocess/managed_shared_memory.hpp"
#include "boost/interprocess/streams/vectorstream.hpp"
#include "test/get_process_id_name.h"
#include <iterator>

#include "glog/logging.h"

using namespace boost::interprocess;

typedef allocator<int, managed_shared_memory::segment_manager> IntAllocator;
typedef allocator<char, managed_shared_memory::segment_manager> CharAllocator;
typedef vector<int, IntAllocator>   MyVector;
typedef basic_string<char, std::char_traits<char>, CharAllocator>  MyString;
typedef basic_vectorstream<MyString>  MyVectorStream;

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

  //<-
#if 1
  managed_shared_memory segment(
      create_only,
      test::get_process_id_name(), //segment name
      65536);           //segment size in bytes
#else
  //->
   managed_shared_memory segment(
      create_only,
      "MySharedMemory", //segment name
      65536);           //segment size in bytes
   //<-
#endif

  MyVector* my_vector = segment.construct<MyVector>("MyVector")
      (IntAllocator(segment.get_segment_manager()));
  //Fill vector
  my_vector->reserve(100);
  for(int i = 0; i < 100; ++i){
    my_vector->push_back(i);
  }

  MyVectorStream myvectorstream(CharAllocator(segment.get_segment_manager()));
  myvectorstream.reserve(100*5);

  //Write all vector elements as text in the internal string
  //Data will be directly written in shared memory, because
  //internal string's allocator is a shared memory allocator
  for(std::size_t i = 0, max = my_vector->size(); i < max; ++i){
    myvectorstream << (*my_vector)[i] << std::endl;
  }
  //Auxiliary vector to compare original data
  MyVector *my_vector_2 = segment.construct<MyVector>("MyVector2")
      (IntAllocator(segment.get_segment_manager()));
  my_vector_2->reserve(100);

  //Extract all values from the internal
  //string directly to a shared memory vector.
  std::istream_iterator<int> it(myvectorstream), itend;
  std::copy(it, itend, std::back_inserter(*my_vector_2));

  //Compare vectors
  assert(std::equal(my_vector->begin(), my_vector->end(), my_vector_2->begin()));

  //Create a copy of the internal string
  MyString stringcopy (myvectorstream.vector());

  //Now we create a new empty shared memory string...
  MyString *mystring =
      segment.construct<MyString>("MyString")
          (CharAllocator(segment.get_segment_manager()));

  //...and we swap vectorstream's internal string
  //with the new one: after this statement mystring
  //will be the owner of the formatted data.
  //No reallocations, no data copies
  myvectorstream.swap_vector(*mystring);

  //Let's compare both strings
  assert(stringcopy == *mystring);

  //Done, destroy and delete vectors and string from the segment
  segment.destroy_ptr(my_vector_2);
  segment.destroy_ptr(my_vector);
  segment.destroy_ptr(mystring);

  return 0;
}