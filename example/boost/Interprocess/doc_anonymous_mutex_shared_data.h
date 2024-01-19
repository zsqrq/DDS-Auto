//
// Created by wz on 24-1-19.
//

#ifndef FAST_DDS_EXAMPLE_EXAMPLE_BOOST_INTERPROCESS_DOC_ANONYMOUS_MUTEX_SHARED_DATA_H_
#define FAST_DDS_EXAMPLE_EXAMPLE_BOOST_INTERPROCESS_DOC_ANONYMOUS_MUTEX_SHARED_DATA_H_
#include "boost/interprocess/detail/config_begin.hpp"
#include "boost/interprocess/sync/interprocess_mutex.hpp"

struct shared_memory_log {
  enum { NumItems = 100 };
  enum { Linesize = 100 };

  shared_memory_log() :
      current_line(0),
      end_a(false),
      end_b(false) {}

  boost::interprocess::interprocess_mutex mutex;

  char items[NumItems][Linesize];
  int current_line;
  bool end_a;
  bool end_b;
};
#include "boost/interprocess/detail/config_end.hpp"
#endif //FAST_DDS_EXAMPLE_EXAMPLE_BOOST_INTERPROCESS_DOC_ANONYMOUS_MUTEX_SHARED_DATA_H_
