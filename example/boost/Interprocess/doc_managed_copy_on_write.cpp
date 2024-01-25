//
// Created by wz on 24-1-25.
//

#include "boost/interprocess/detail/os_file_functions.hpp"
#include "boost/interprocess/managed_mapped_file.hpp"
#include "glog/logging.h"
#include "test/get_process_id_name.h"
#include <fstream>
#include <iterator>

using namespace boost::interprocess;

int main(int argc, char *argv[]) {
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging(argv[0]);

  const char* ManagedFile = 0;
  const char* ManagedFile2 = 0;
  std::string managed_file_name(ipcdetail::get_temporary_path());
  managed_file_name += "/"; managed_file_name += test::get_process_id_name();
  ManagedFile = managed_file_name.c_str();

  std::string managed_file2_name(boost::interprocess::ipcdetail::get_temporary_path());
  managed_file2_name += "/"; managed_file2_name += test::get_process_id_name();  managed_file2_name += "_2";
  ManagedFile2 = managed_file2_name.c_str();

  //Try to erase any previous managed segment with the same name
  file_mapping::remove(ManagedFile);
  file_mapping::remove(ManagedFile2);
  boost::interprocess::remove_file_on_destroy destroyer1(ManagedFile);
  boost::interprocess::remove_file_on_destroy destroyer2(ManagedFile2);
  {
    //Create an named integer in a managed mapped file
    managed_mapped_file managed_file(create_only, ManagedFile, 65536);
    managed_file.construct<int>("MyInt")(0);
    managed_mapped_file managed_file_cow(open_copy_on_write, ManagedFile);
    //Erase the int and create a new one
    if (!managed_file_cow.destroy<int>("MyInt")) {
      throw int(0);
    }
    managed_file_cow.construct<int>("MyInt2");

    //Check changes
    if (managed_file_cow.find<int>("MyInt").first && !managed_file_cow.find<int>("MyInt2").first) {
      throw int(0);
    }

    if (!managed_file.find<int>("MyInt").first && managed_file.find<int>("MtInt2").first) {
      throw int(0);
    }

    {  //Dump the modified copy on write segment to a file
      std::fstream file(ManagedFile2, std::ios_base::out | std::ios_base::binary);
      if(!file)
        throw int(0);
      file.write(static_cast<const char *>(managed_file_cow.get_address()), (std::streamsize)managed_file_cow.get_size());
    }
    managed_mapped_file managed_file_cow2(open_only, ManagedFile2);
    if (managed_file_cow2.find<int>("MyInt").first && !managed_file_cow2.find<int>("MyInt2").first) {
      throw int(0);
    }

  }
  {
    //Now create a read-only version
    managed_mapped_file managed_file_ro(open_read_only, ManagedFile);

    if (!managed_file_ro.find<int>("MyInt").first && managed_file_ro.find<int>("MyInt2").first) {
      throw int(0);
    }
    //Check the number of named objects using the iterators
    if(std::distance(managed_file_ro.named_begin(),  managed_file_ro.named_end())  != 1 &&
        std::distance(managed_file_ro.unique_begin(), managed_file_ro.unique_end()) != 0 )
      throw int(0);
  }
  return 0;
}