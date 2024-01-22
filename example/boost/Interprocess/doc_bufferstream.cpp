//
// Created by wz on 24-1-22.
//
#include "boost/interprocess/detail/workaround.hpp"
#include "boost/interprocess/managed_shared_memory.hpp"
#include "boost/interprocess/streams/bufferstream.hpp"
#include "glog/logging.h"
#include <vector>
#include <iterator>
#include <cstddef>
#include "test/get_process_id_name.h"

int main() {
  using namespace boost::interprocess;
  FLAGS_minloglevel = 0;
  FLAGS_alsologtostderr = 1;
  google::InitGoogleLogging("bufferstream");

  struct shm_remove {
    shm_remove() {
      boost::interprocess::shared_memory_object::remove(test::get_process_id_name());
    }
    ~shm_remove() {
      shared_memory_object::remove(test::get_process_id_name());
    }
  } remover;
  (void) remover;

  managed_shared_memory segment(create_only, test::get_process_id_name(),65536);
  std::vector<int> data;
  data.reserve(100);

  for (size_t i = 0; i < 100; ++i) {
    data.push_back(i);
  }
  const std::size_t BufferSize = 100 * 5;
  char* my_cstring = segment.construct<char>("MyCString")[BufferSize]('\0');

  bufferstream mybufferstream(my_cstring, BufferSize);
  for (size_t i = 0; i < 100; ++i) {
    mybufferstream << data[i] << std::endl;
  }
  assert(mybufferstream.good());

  std::vector<int> data2;
  std::istream_iterator<int> it(mybufferstream), itend;
  std::copy(it, itend, std::back_inserter(data2));

  assert(mybufferstream.fail());
  assert(std::equal(data.begin(), data.end(), data2.begin()));

  mybufferstream.clear();
  mybufferstream.seekp(0, std::ios::beg);

  for(std::size_t i = 0, m = data.size()*5; i < m; ++i){
    mybufferstream << data[i%5u] << std::endl;
  }
  assert(!mybufferstream.good());
  assert(mybufferstream.bad());
  segment.destroy_ptr(my_cstring);
  return 0;
}