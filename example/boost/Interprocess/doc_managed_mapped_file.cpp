//
// Created by wz on 24-1-25.
//
#include "boost/interprocess/detail/workaround.hpp"
#if defined(BOOST_INTERPROCESS_MAPPED_FILES)
#include "boost/interprocess/containers/list.hpp"
#include "boost/interprocess/managed_mapped_file.hpp"
#include "boost/interprocess/allocators/allocator.hpp"
#include "test/get_process_id_name.h"
#include "glog/logging.h"

#include <cstddef>
#include <cstdio>

using namespace boost::interprocess;
using MyList =
    boost::interprocess::list<int,
                              allocator<int,
                                        managed_mapped_file::segment_manager>>;

int main(int argc, char *argv[]) {
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging(argv[0]);
  //Define file names
  //<-
#if 1
  std::string file(boost::interprocess::ipcdetail::get_temporary_path());
  file += "/"; file += test::get_process_id_name();
  const char *FileName = file.c_str();
#else
  //->
   const char *FileName       = "file_mapping";
   //<-
#endif
  const std::size_t FileSize = 1000;
  file_mapping::remove(FileName);

  BOOST_TRY {
      MyList::size_type old_size = 0;
      managed_mapped_file::handle_t list_handle;
      {
        managed_mapped_file mfile_memory(create_only, FileName, FileSize);
        MyList *mylist = mfile_memory.construct<MyList>("MyList")
            (mfile_memory.get_segment_manager());

        //Obtain handle, that identifies the list in the buffer
        list_handle = mfile_memory.get_handle_from_address(mylist);
        BOOST_TRY{
            while(1) {
              mylist->insert(mylist->begin(), 0);
            }
          }
          BOOST_CATCH(const bad_alloc &){
            //mapped file is full
        } BOOST_CATCH_END
        old_size = mylist->size();
      }

      // make the list bigger, let's increase the mapped file
      //in FileSize bytes more.
      managed_mapped_file::grow(FileName, FileSize*2);
      {
        managed_mapped_file mfile_memory(open_only, FileName);

        //If mapping address has changed, the old pointer is invalid,
        //so use previously obtained handle to find the new pointer.
        MyList *mylist = static_cast<MyList *>
        (mfile_memory.get_address_from_handle(list_handle));
        //Fill list until there is no more room in the file
        BOOST_TRY{
            while(1) {
              mylist->insert(mylist->begin(), 0);
            }
          }
          BOOST_CATCH(const bad_alloc &){
            //mapped file is full
        } BOOST_CATCH_END
        MyList::size_type new_size = mylist->size();

        //Destroy list
        mfile_memory.destroy_ptr(mylist);

        return (new_size > old_size) ? 0 : 1;
      }
  }BOOST_CATCH(...) {
      file_mapping::remove(FileName);
      BOOST_RETHROW
  }BOOST_CATCH_END
  file_mapping::remove(FileName);
  return 0;
}

#else //#if defined(BOOST_INTERPROCESS_MAPPED_FILES)
int main()
{
   return 0;
}
#endif//#if defined(BOOST_INTERPROCESS_MAPPED_FILES)
