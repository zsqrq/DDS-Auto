//
// Created by wz on 24-1-19.
//

#ifndef FAST_DDS_EXAMPLE_EXAMPLE_BOOST_INTERPROCESS_DOC_ANONYMOUS_CONDITION_SHARED_DATA_H_
#define FAST_DDS_EXAMPLE_EXAMPLE_BOOST_INTERPROCESS_DOC_ANONYMOUS_CONDITION_SHARED_DATA_H_

#include "boost/interprocess/detail/config_begin.hpp"
#include "boost/interprocess/sync/interprocess_mutex.hpp"
#include "boost/interprocess/sync/interprocess_condition.hpp"

struct trace_queue {
  enum { LineSize = 100};
  trace_queue() : message_in(false) {}

  boost::interprocess::interprocess_mutex mutex;

  boost::interprocess::interprocess_condition cond_empty;

  boost::interprocess::interprocess_condition cond_full;

  char items[LineSize];

  bool message_in;
};

#endif //FAST_DDS_EXAMPLE_EXAMPLE_BOOST_INTERPROCESS_DOC_ANONYMOUS_CONDITION_SHARED_DATA_H_
