//
// Created by wz on 24-1-25.
//

#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <fstream>
#include <iostream>
#include <cstdio>
#include "glog/logging.h"
#include "test/get_process_id_name.h"

using namespace boost::interprocess;

int main(int argc, char *argv[]) {
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging(argv[0]);

  BOOST_TRY{
      struct file_remove
      {
        //<-
#if 1
        file_remove() { std::remove(test::get_process_id_name()); }
        ~file_remove(){ std::remove(test::get_process_id_name()); }
#else
        //->
         file_remove() { std::remove("file_name"); }
         ~file_remove(){ std::remove("file_name"); }
      //<-
#endif
        //->
      } file_remover;
      struct mutex_remove
      {
        //<-
#if 1
        mutex_remove() { named_mutex::remove(test::get_process_id_name()); }
        ~mutex_remove(){ named_mutex::remove(test::get_process_id_name()); }
#else
        //->
         mutex_remove() { named_mutex::remove("fstream_named_mutex"); }
         ~mutex_remove(){ named_mutex::remove("fstream_named_mutex"); }
      //<-
#endif
        //->
      } remover;
      //<-
      (void)remover;
      //->

      //Open or create the named mutex
      //<-
#if 1
      named_mutex mutex(open_or_create, test::get_process_id_name());
#else
      //->
      named_mutex mutex(open_or_create, "fstream_named_mutex");
   //<-
#endif
      //->

      //<-
#if 1
      std::ofstream file(test::get_process_id_name());
#else
      //->
      std::ofstream file("file_name");
      //<-
#endif
      //->

      for(int i = 0; i < 10; ++i){

        //Do some operations...

        //Write to file atomically
        scoped_lock<named_mutex> lock(mutex);
        file << "Process name, ";
        file << "This is iteration #" << i;
        file << std::endl;
      }
    }
    BOOST_CATCH(interprocess_exception &ex){
      std::cout << ex.what() << std::endl;
      return 1;
    } BOOST_CATCH_END
  return 0;
}