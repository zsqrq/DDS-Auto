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
  google::InitGoogleLogging("MessageQueueB");

  BOOST_TRY {
    boost::interprocess::message_queue mq(boost::interprocess::open_only,
                                          "message_queue_A");
    unsigned int priority;
    boost::interprocess::message_queue::size_type recvd_size;

    for (int i = 0; i < 100; ++i) {
      int number;
      mq.receive(&number, sizeof(number), recvd_size, priority);
      LOG(INFO) << "Message Queue B Got message : " << number;
      if (number != i || recvd_size != sizeof(number))
        return 1;
      boost::this_thread::sleep(boost::posix_time::milliseconds(200));
    }
  } BOOST_CATCH(boost::interprocess::interprocess_exception& ex) {
    boost::interprocess::message_queue::remove("message_queue_A");
      LOG(ERROR) << ex.what();
      return 1;
  }BOOST_CATCH_END
  boost::interprocess::message_queue::remove("message_queue_A");
  return 0;
}