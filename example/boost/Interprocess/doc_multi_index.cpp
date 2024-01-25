//
// Created by wz on 24-1-25.
//
#include "boost/interprocess/detail/workaround.hpp"
#include "boost/interprocess/managed_shared_memory.hpp"
#include "boost/interprocess/allocators/allocator.hpp"
#include "boost/interprocess/containers/string.hpp"
#include "boost/interprocess/detail/config_external_begin.hpp"
#include "boost/interprocess/detail/config_external_end.hpp"
#include "boost/multi_index_container.hpp"
#include "boost/multi_index/member.hpp"
#include "boost/multi_index/ordered_index.hpp"
#include "test/get_process_id_name.h"
#include "glog/logging.h"

using namespace boost::interprocess;
namespace bmi = boost::multi_index;
using char_allocator = managed_shared_memory::allocator<char>::type;
using shm_string = basic_string<char, std::char_traits<char>, char_allocator>;

struct employee {
  int id;
  int age;
  shm_string name;
  employee(int id_, int age_, const char* name_, const char_allocator& a)
      : id(id_), age(age_), name(name_, a) {}
};

//Tags
struct id{};
struct age{};
struct name{};

typedef bmi::multi_index_container<
    employee,
    bmi::indexed_by<
        bmi::ordered_unique
            <bmi::tag<id>,  bmi::member<employee,int,&employee::id> >,
        bmi::ordered_non_unique<
            bmi::tag<name>, bmi::member<employee,shm_string,&employee::name> >,
        bmi::ordered_non_unique
            <bmi::tag<age>, bmi::member<employee,int,&employee::age> > >,
    managed_shared_memory::allocator<employee>::type> employee_set;

int main(int argc, char *argv[]) {
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging(argv[0]);

  //Remove shared memory on construction and destruction
  struct shm_remove
  {
    //<-
#if 1
    shm_remove() { shared_memory_object::remove(test::get_process_id_name()); }
    ~shm_remove(){ shared_memory_object::remove(test::get_process_id_name()); }
#else
    //->
      shm_remove() { shared_memory_object::remove("MySharedMemory"); }
      ~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
   //<-
#endif
    //->
  } remover;
  //<-
  (void)remover;
  //->employee_sets

  //Create shared memory
  //<-
#if 1
  managed_shared_memory segment(create_only,test::get_process_id_name(), 65536);
#else
  //->
   managed_shared_memory segment(create_only,"MySharedMemory", 65536);
   //<-
#endif

  employee_set *employee_sets = segment.construct<employee_set>
      ("My_MultiIndex_Container")(employee_set::ctor_args_list(),
          segment.get_allocator<employee>());
  char_allocator ca(segment.get_allocator<char>());
  employee_sets->insert(employee(0,31, "Joe", ca));
  employee_sets->insert(employee(1,27, "Robert", ca));
  employee_sets->insert(employee(2,40, "John", ca));
  return 0;
}