//
// Created by wz on 24-1-22.
//

#ifndef FAST_DDS_EXAMPLE_EXAMPLE_BOOST_INTERPROCESS_TEST_GET_PROCESS_ID_NAME_H_
#define FAST_DDS_EXAMPLE_EXAMPLE_BOOST_INTERPROCESS_TEST_GET_PROCESS_ID_NAME_H_
#include "boost/config.hpp"
#include "boost/interprocess/detail/os_thread_functions.hpp"
#include "boost/interprocess/detail/os_file_functions.hpp"
#include "glog/logging.h"
#include <string>
#include <sstream>

namespace boost {
namespace interprocess {
namespace test {

inline void get_process_id_name(std::string &str) {
  std::stringstream sstr;
  sstr << "process_" << boost::interprocess::ipcdetail::get_current_process_id() << std::ends;
  str = sstr.str().c_str();
}

inline void get_process_id_ptr_name(std::string &str, const void *ptr) {
  std::stringstream sstr;
  sstr << "process_" << boost::interprocess::ipcdetail::get_current_process_id() << "_" << ptr << std::ends;
  str = sstr.str().c_str();
}

inline const char *get_process_id_name() {
  static bool done = false;
  static std::string str;
  if (!done) {
    get_process_id_name(str);
  }
  return str.c_str();
}

inline const char *get_process_id_ptr_name(void *ptr) {
  static bool done = false;
  static std::string str;
  if (!done)
    get_process_id_ptr_name(str, ptr);
  return str.c_str();
}

inline const char *add_to_process_id_name(const char *name) {
  static bool done = false;
  static std::string str;
  if (!done) {
    get_process_id_name(str);
    str += name;
  }
  return str.c_str();
}

inline const char *add_to_process_id_ptr_name(const char *name, void *ptr) {
  static bool done = false;
  static std::string str;
  if (!done) {
    get_process_id_ptr_name(str, ptr);
    str += name;
  }
  return str.c_str();
}

}

inline std::string get_filename()
{
  std::string ret (ipcdetail::get_temporary_path());
  ret += "/";
  ret += test::get_process_id_name();
  return ret;
}
#ifdef BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES
namespace test {

inline void get_process_id_wname(std::wstring &str)
{
   std::wstringstream sstr;
   sstr << L"process_" << boost::interprocess::ipcdetail::get_current_process_id() << std::ends;
   str = sstr.str().c_str();
}

inline const wchar_t *get_process_id_wname()
{
   static bool done = false;
   static std::wstring str;
   if(!done)
      get_process_id_wname(str);

   return str.c_str();
}

inline const wchar_t *add_to_process_id_name(const wchar_t *name)
{
   static bool done = false;
   static std::wstring str;
   if(!done){
      get_process_id_wname(str);
      str += name;
   }
   return str.c_str();
}
}

inline std::wstring get_wfilename()
{
   std::wstring ret (ipcdetail::get_temporary_wpath());
   ret += L"/";
   ret += test::get_process_id_wname();
   return ret;
}
#endif
}

}

#endif //FAST_DDS_EXAMPLE_EXAMPLE_BOOST_INTERPROCESS_TEST_GET_PROCESS_ID_NAME_H_
