//
// Created by wz on 24-1-22.
//

#ifndef FAST_DDS_EXAMPLE_EXAMPLE_BOOST_INTERPROCESS_UPGRADABLE_MUTEX_SHARED_DATA_H_
#define FAST_DDS_EXAMPLE_EXAMPLE_BOOST_INTERPROCESS_UPGRADABLE_MUTEX_SHARED_DATA_H_

#include "boost/interprocess/sync/interprocess_upgradable_mutex.hpp"

struct shared_data {
  enum { NumItems = 100 };
  enum { LineSize = 100 };

  shared_data()
      : current_line(0),
        end_a(false),
        end_b(false) {}

  boost::interprocess::interprocess_upgradable_mutex upgradable_mutex;

  char items[NumItems][LineSize];
  int current_line;
  bool end_a;
  bool end_b;
};

#endif //FAST_DDS_EXAMPLE_EXAMPLE_BOOST_INTERPROCESS_UPGRADABLE_MUTEX_SHARED_DATA_H_
