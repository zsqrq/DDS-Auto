//
// Created by wz on 24-1-24.
//

#include "boost/interprocess/managed_shared_memory.hpp"
#include "test/get_process_id_name.h"
#include "glog/logging.h"
#include <cassert>

using namespace boost::interprocess;

int main(int argc, char* argv[]) {
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging(argv[0]);

  struct shm_remove {
    shm_remove() {
      shared_memory_object::remove(test::get_process_id_name());
    }
    ~shm_remove() {
      shared_memory_object::remove(test::get_process_id_name());
    }
  } remover;
  (void)remover;

  managed_shared_memory managed_shm(create_only, test::get_process_id_name(),65536);

  const std::size_t Alignment = 128;
  void *ptr = managed_shm.allocate_aligned(100, Alignment);
  const char* zero_addr = static_cast<char *>(0);
  //Check alignment
  if (size_t(static_cast<char*>(ptr) - static_cast<char *>(0)) % Alignment == 0) {
    LOG(INFO) << "Allocate shared memory alligned to 128" << size_t(zero_addr);
  }

  //Deallocate it
  managed_shm.deallocate(ptr);

  //Non throwing version
  ptr = managed_shm.allocate_aligned(100, Alignment, std::nothrow);
  //Check alignment
  if (std::size_t(static_cast<char*>(ptr)-static_cast<char*>(0)) % Alignment == 0) {
    LOG(INFO) << "Allocate shared memory alligned to 128";
  }
  managed_shm.deallocate(ptr);

  if (Alignment > managed_shared_memory::PayloadPerAllocation) {
    LOG(INFO) << "efficiently allocate aligned blocks of memory use managed_shared_memory::PayloadPerAllocation value";
  }

  ptr = managed_shm.allocate_aligned
      (3u*Alignment - managed_shared_memory::PayloadPerAllocation, Alignment);

  assert(std::size_t(static_cast<char*>(ptr)-static_cast<char*>(0)) % Alignment == 0);

  //Deallocate it
  managed_shm.deallocate(ptr);
  return 0;
}