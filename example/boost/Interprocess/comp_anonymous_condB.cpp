//
// Created by wz on 24-1-19.
//
#include "boost/interprocess/shared_memory_object.hpp"
#include "boost/interprocess/mapped_region.hpp"
#include "boost/interprocess/sync/scoped_lock.hpp"
#include "glog/logging.h"
#include "doc_anonymous_condition_shared_data.h"

int main() {
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging("conditionB");

  boost::interprocess::shared_memory_object shm(boost::interprocess::open_only,
                                                "MySharedMemory",
                                                boost::interprocess::read_write);

  BOOST_TRY {
      boost::interprocess::mapped_region region(shm,
                                                boost::interprocess::read_write);
      auto addr = region.get_address();
      auto data = static_cast<trace_queue*>(addr);
      bool end_loop = false;
      do {
        boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(data->mutex);
        if (!data->message_in) {
          data->cond_empty.wait(lock);
        }
        if (std::strcmp(data->items, "last message") == 0) {
          end_loop = true;
        } else {
          LOG(INFO) << "Process B Received message : "<< data->items;
          data->message_in = false;
          data->cond_full.notify_one();
        }
      } while (!end_loop);
    }
    BOOST_CATCH(boost::interprocess::interprocess_exception& e) {
      LOG(ERROR) << e.what();
      return 1;
    }
  BOOST_CATCH_END
  return 0;
}