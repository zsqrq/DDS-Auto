//
// Created by wz on 24-1-23.
//
#include "boost/interprocess/detail/workaround.hpp"
#include "boost/interprocess/managed_shared_memory.hpp"
#include "boost/interprocess/allocators/allocator.hpp"
#include "boost/interprocess/containers/map.hpp"
#include "boost/interprocess/containers/vector.hpp"
#include "boost/interprocess/containers/string.hpp"
#include "test/get_process_id_name.h"

using namespace boost::interprocess;

using segment_manager_t = managed_shared_memory::segment_manager;
using void_allocator = allocator<void, segment_manager_t>;
using int_allocator = allocator<int, segment_manager_t>;
using int_vector = allocator<int, int_allocator>;
using int_vector_allocator = allocator<int_vector, segment_manager_t>;
using int_vector_vector = vector<int_vector, int_vector_allocator>;
using char_allocator = allocator<char,segment_manager_t>;
using char_string = basic_string<char, std::char_traits<char>, char_allocator>;

class complex_data {
 private:
  int id_;
  char_string char_string_;
  int_vector_vector int_vector_vector_;
 public:
  complex_data(int id, const char* name, const void_allocator& void_alloc)
  : id_(id), char_string_(name, void_alloc), int_vector_vector_(void_alloc) {}

  int get_id() {
    return id_;
  }
  char_string get_char_string() {
    return char_string_;
  }
  int_vector_vector get_int_vector_vector() {
    return int_vector_vector_;
  }
};

using map_value_type = std::pair<const char_string, complex_data>;
using movable_to_map_value_type = std::pair<char_string, complex_data>;
using map_value_type_allocator = allocator<map_value_type, segment_manager_t>;
using complex_map_type = map<char_string,complex_data, std::less<char_string>, map_value_type_allocator>;

int main() {
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
  managed_shared_memory segment(create_only,test::get_process_id_name(), 65536);
#else
  //->
   managed_shared_memory segment(create_only,"MySharedMemory", 65536);
   //<-
#endif

//An allocator convertible to any allocator<T, segment_manager_t> type
  void_allocator alloc_inst (segment.get_segment_manager());

  complex_map_type *mymap =
      segment.construct<complex_map_type>("MyMap")(std::less<char_string>(), alloc_inst);

  for (int i = 0; i < 100; ++i) {
    char_string key_object(alloc_inst);
    complex_data mapped_object(i, "default_name", alloc_inst);
    map_value_type value(key_object, mapped_object);
    mymap->insert(value);
  }
  return 0;
}


