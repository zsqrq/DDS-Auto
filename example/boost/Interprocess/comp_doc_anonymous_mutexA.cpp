//
// Created by wz on 24-1-19.
//
#include "boost/interprocess/shared_memory_object.hpp"
#include "boost/interprocess/mapped_region.hpp"
#include "boost/interprocess/sync/scoped_lock.hpp"
#include "doc_anonymous_mutex_shared_data.h"
#include "glog/logging.h"

int main() {
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging("intra_mutexA");
  BOOST_TRY {
      struct shm_remove {
        shm_remove() {
          boost::interprocess::shared_memory_object::remove("MyMutexSharedMemory");
        }
        ~shm_remove() {
          boost::interprocess::shared_memory_object::remove("MyMutexSharedMemory");
        }
      } remover;
      (void) remover;

      boost::interprocess::shared_memory_object shm(boost::interprocess::create_only,
                                                    "MyMutexSharedMemory",
                                                    boost::interprocess::read_write);
      shm.truncate(sizeof(shared_memory_log));

      boost::interprocess::mapped_region region(shm,
                                                boost::interprocess::read_write);
      auto addr = region.get_address();
      auto data = new (addr) shared_memory_log;

      for (int i = 0; i < shared_memory_log::NumItems; ++i) {
        boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(data->mutex);
        std::sprintf(data->items[(data->current_line++) % shared_memory_log::NumItems],
                      "%s_%d", "Interprocess Shared Mutex A",i);
        LOG(INFO) << "Process A published Message : " << data->items;
        if (i == (shared_memory_log::NumItems)) {
          data->end_a = true;
        }
      }
      while (true) {
        boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(data->mutex);
        if (data->end_b) break;
      }
    } BOOST_CATCH(boost::interprocess::interprocess_exception &ex) {
      LOG(ERROR) << ex.what();
      return 1;
    }
  BOOST_CATCH_END
  return 0;
}