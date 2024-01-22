//
// Created by wz on 24-1-22.
//

#ifndef FAST_DDS_EXAMPLE_EXAMPLE_BOOST_INTERPROCESS_DOC_ANONYMOUS_SEMAPHORE_SHARED_DATA_H_
#define FAST_DDS_EXAMPLE_EXAMPLE_BOOST_INTERPROCESS_DOC_ANONYMOUS_SEMAPHORE_SHARED_DATA_H_
#include "boost/interprocess/sync/interprocess_semaphore.hpp"

struct shared_memory_buffer {
  enum { NumItems = 10 };
  shared_memory_buffer() :
  mutex(1), nempty(1), nstored(0) {}

  boost::interprocess::interprocess_semaphore mutex;
  boost::interprocess::interprocess_semaphore nempty;
  boost::interprocess::interprocess_semaphore nstored;

  int items[NumItems];
};

#endif //FAST_DDS_EXAMPLE_EXAMPLE_BOOST_INTERPROCESS_DOC_ANONYMOUS_SEMAPHORE_SHARED_DATA_H_
