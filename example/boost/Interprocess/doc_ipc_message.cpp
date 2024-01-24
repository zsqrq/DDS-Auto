//
// Created by wz on 24-1-24.
//
#include "boost/interprocess/detail/workaround.hpp"
#include "boost/interprocess/managed_shared_memory.hpp"
#include "glog/logging.h"
#include "test/get_process_id_name.h"
#include <cstdlib>
#include <sstream>

int main(int argc, char* argv[]) {
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging(argv[0]);

  using namespace boost::interprocess;

  if (argc == 1 ) {
    struct shm_remove {
      shm_remove() {
        shared_memory_object::remove(test::get_process_id_name());
      }
      ~shm_remove() {
        shared_memory_object::remove(test::get_process_id_name());
      }
    } remover;
    (void)remover;
    managed_shared_memory segment(create_only, test::get_process_id_name(), 65536);

    //Allocate a portion of the segment (raw memory)
    managed_shared_memory::size_type  free_memory = segment.get_free_memory();
    void* shptr = segment.allocate(1024);
    std::memset(shptr,10, 1024);

    //Check invariant
    if (free_memory <= segment.get_free_memory()) {
      LOG(ERROR) << "Avaliable memory is not enougth";
      return 1;
    }

    //An handle from the base address can identify any byte of the shared
    //memory segment even if it is mapped in different base addresses
    managed_shared_memory::handle_t handle = segment.get_handle_from_address(shptr);
    std::stringstream ss;
    ss << argv[0] << " " << handle;
    ss << " "<< test::get_process_id_name();
    ss << std::ends;

    if (0 != std::system(ss.str().c_str())) {
      LOG(ERROR) << "Failed to excuted Cli Command";
      return 1;
    }
    if (free_memory != segment.get_free_memory()) {
      LOG(ERROR) << "Allocate Memory Size Not Right";
      return 1;
    }
  } else {
    managed_shared_memory segment(open_only,argv[2]);
    managed_shared_memory::handle_t handle = 0;
    //Obtain handle value
    std::stringstream s; s << argv[1]; s >> handle;

    //Get buffer local address from handle
    void* msg = segment.get_address_from_handle(handle);
    const char *mem = static_cast<char*>(msg);
    LOG(INFO) << "Got buffer msg : "<< std::to_string(*mem);
    segment.deallocate(msg);
  }
  return 0;
}