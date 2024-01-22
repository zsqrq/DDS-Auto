//
// Created by wz on 24-1-22.
//
#include "boost/date_time.hpp"
#include "boost/thread.hpp"
#include "boost/interprocess/ipc/message_queue.hpp"
#include "glog/logging.h"
#include <iostream>
#include <vector>

int main() {
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging("MessageQueueA");

  BOOST_TRY {
      boost::interprocess::message_queue::remove("message_queue_A");

      boost::interprocess::message_queue mq(boost::interprocess::create_only,
                                            "message_queue_A",
                                            100,
                                            sizeof(int));
      for (int i = 0; i < 100; ++i) {
        mq.send(&i, sizeof(i), 0);
        LOG(INFO) << "Message Queue A Sent message : " << i;
        boost::this_thread::sleep(boost::posix_time::milliseconds(200));
      }
    } BOOST_CATCH(boost::interprocess::interprocess_exception& ex) {
      LOG(ERROR) << ex.what();
      return 1;
  } BOOST_CATCH_END
  return 0;
}