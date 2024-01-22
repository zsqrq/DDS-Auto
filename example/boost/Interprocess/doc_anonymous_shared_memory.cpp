//
// Created by wz on 24-1-22.
//
#include "boost/interprocess/anonymous_shared_memory.hpp"
#include "boost/interprocess/mapped_region.hpp"
#include "glog/logging.h"
#include <iostream>
#include <cstring>

int main(int argc, char** argv) {
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging(argv[0]);
  using boost::interprocess::anonymous_shared_memory;
  using boost::interprocess::mapped_region;
  BOOST_TRY {
      mapped_region region(anonymous_shared_memory(1000));
      std::memset(region.get_address(), 1, region.get_size());
  } BOOST_CATCH(boost::interprocess::interprocess_exception& ex) {
      LOG(ERROR) << ex.what();
      return 1;
  } BOOST_CATCH_END
  return 0;
}