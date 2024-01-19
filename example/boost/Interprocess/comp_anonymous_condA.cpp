//
// Created by wz on 24-1-19.
//

#include "boost/date_time.hpp"
#include "boost/thread.hpp"
#include "boost/interprocess/shared_memory_object.hpp"
#include "boost/interprocess/mapped_region.hpp"
#include "boost/interprocess/sync/scoped_lock.hpp"
#include "glog/logging.h"
#include "doc_anonymous_condition_shared_data.h"

int main() {
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging("conditionA");

  struct shm_remove {
    shm_remove() {
      boost::interprocess::shared_memory_object::remove("MySharedMemory");
    }

    ~shm_remove() {
      boost::interprocess::shared_memory_object::remove("MySharedMemory");
    }
  } remover;

  (void) remover;

  boost::interprocess::shared_memory_object shm(boost::interprocess::create_only,
                                                "MySharedMemory",
                                                boost::interprocess::read_write);

  BOOST_TRY {
      shm.truncate(sizeof(trace_queue));
      boost::interprocess::mapped_region region(shm,boost::interprocess::read_write);

      auto addr = region.get_address();
      auto data = new (addr) trace_queue;
      const int NumMsg = 100;

      for (int i = 0; i < NumMsg; ++i) {
        boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(data->mutex);
        if (data->message_in) {
          data->cond_full.wait(lock);
        }
        if (i == (NumMsg - 1)) {
          LOG(INFO) << data->items << "last message :" ;
          std::sprintf(data->items, "%s", "last message");
        } else {
          std::sprintf(data->items, "%s_%d", "My_SharedMemory_Message", i);
          LOG(INFO) << "Process A Published Message : " <<data->items ;
        }
        data->cond_empty.notify_one();
        data->message_in = true;
        boost::this_thread::sleep(boost::posix_time::milliseconds(100));
      }
    }
    BOOST_CATCH(boost::interprocess::interprocess_exception& e) {
      LOG(ERROR) << e.what();
      return 1;
    }
  BOOST_CATCH_END
  return 0;
}