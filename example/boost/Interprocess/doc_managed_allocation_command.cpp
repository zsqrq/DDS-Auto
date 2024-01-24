//
// Created by wz on 24-1-24.
//

#include "boost/interprocess/managed_shared_memory.hpp"
#include "test/get_process_id_name.h"
#include "glog/logging.h"
#include <cassert>

using namespace boost::interprocess;

int main(int argc, char *argv[]) {
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging(argv[0]);

  struct shm_remove
  {
    shm_remove() { shared_memory_object::remove(test::get_process_id_name()); }
    ~shm_remove(){ shared_memory_object::remove(test::get_process_id_name()); }
  } remover;
  //<-
  (void)remover;

  //Managed memory segment that allocates portions of a shared memory
  //segment with the default management algorithm
  managed_shared_memory managed_shm(create_only, test::get_process_id_name(), 10000*sizeof(std::size_t));

  //Allocate at least 100 bytes, 1000 bytes if possible
  managed_shared_memory::size_type min_size = 100;
  managed_shared_memory::size_type first_received_size = 1000;
  size_t *hint = 0;
  std::size_t *ptr = managed_shm.allocation_command<size_t>(
      boost::interprocess::allocate_new, min_size, first_received_size, hint
      );

  //Received size must be bigger than min_size
  if (first_received_size >= min_size) {
    LOG(INFO) << "first_received_size bigger than min_size";
  }

  //Get free memory
  managed_shared_memory::size_type free_memory_after_allocation = managed_shm.get_free_memory();
  (void)free_memory_after_allocation;

  for (std::size_t i = 0; i < first_received_size; ++i) {
    ptr[i] = i;
  }
  min_size = first_received_size * 2;
  managed_shared_memory::size_type expanded_size = first_received_size * 3;
  size_t *ret = managed_shm.allocation_command(expand_fwd,min_size,expanded_size,ptr);
  (void)ret;

  //Check invariants
  assert(ptr != 0);
  assert(ret == ptr);
  assert(expanded_size >= first_received_size*2);

  //Get free memory and compare
  managed_shared_memory::size_type free_memory_after_expansion = managed_shm.get_free_memory();
  assert(free_memory_after_expansion < free_memory_after_allocation);
  (void)free_memory_after_expansion;

  //Write new values
  for (std::size_t i = first_received_size; i < expanded_size; ++i) ptr[i] = i;

  //Try to shrink approximately to min_size, but the new size
  //should be smaller than min_size*2.
  //This "should" be successful since no other class is allocating
  //memory from the segment
  managed_shared_memory::size_type shrunk_size = min_size;
  ret = managed_shm.allocation_command
      (boost::interprocess::shrink_in_place, min_size*2, shrunk_size, ptr);

//Check invariants
  assert(ptr != 0);
  assert(ret == ptr);
  assert(shrunk_size <= min_size*2);
  assert(shrunk_size >= min_size);

  //Get free memory and compare
  managed_shared_memory::size_type free_memory_after_shrinking = managed_shm.get_free_memory();
  assert(free_memory_after_shrinking > free_memory_after_expansion);
  //<-
  (void)free_memory_after_shrinking;
  //->

  //Deallocate the buffer
  managed_shm.deallocate(ptr);
  return 0;
}