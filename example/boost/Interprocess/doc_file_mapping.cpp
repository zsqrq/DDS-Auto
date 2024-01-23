//
// Created by wz on 24-1-23.
//
#include "boost/interprocess/file_mapping.hpp"
#include "boost/interprocess/mapped_region.hpp"
#include "glog/logging.h"
#include "test/get_process_id_name.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstddef>
#include <cstdlib>

int main(int argc, char** argv) {
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging(argv[0]);
  using namespace boost::interprocess;

  std::string file_name(ipcdetail::get_temporary_path());
  file_name += "/";
  file_name += test::get_process_id_name();
  const char *FileName = "file_mapping.bin";

  const std::size_t Filesize = 10000;
  if (argc == 1) {
    {
      file_mapping::remove(FileName);
      std::filebuf fbuf;
      fbuf.open(FileName, std::ios_base::in | std::ios_base::out | std::ios_base::trunc |
          std::ios_base::binary);
      fbuf.pubseekoff(Filesize - 1, std::ios_base::beg);
      fbuf.sputc(0);
    }

    struct file_remove {
      file_remove(const char* FileName)
          : FileName_(FileName) {}
      ~file_remove() {
        file_mapping::remove(FileName_);
      }
      const char* FileName_;
    }remover(FileName);

    //Create a file mapping
    file_mapping m_file(FileName, read_write);

    //Map the whole file with read-write permissions in this process
    mapped_region region(m_file, read_write);

    //Get the address of the mapped region
    void* addr = region.get_address();

  }

}