//
// Created by wz on 24-1-26.
//

#include <boost/interprocess/detail/workaround.hpp>
//[doc_scoped_ptr
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/smart_ptr/scoped_ptr.hpp>
//<-
#include "test/get_process_id_name.h"
#include "glog/logging.h"

using namespace boost::interprocess;

class my_class{};
class my_exception{};

template<typename T>
class my_deleter {
 private:
  using segment_manager = managed_shared_memory::segment_manager;
  segment_manager *mp_segment_manager;

 public:
  using pointer = T*;
  my_deleter(segment_manager* s_mngr)
  :mp_segment_manager(s_mngr){}

  void operator()(pointer object_to_delete) {
    mp_segment_manager->destroy_ptr(object_to_delete);
  }
};

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
  //->

  //<-
#if 1
  managed_shared_memory shmem(create_only, test::get_process_id_name(), 10000);
#else
  //->
   managed_shared_memory shmem(create_only, "MySharedMemory", 10000);
   //<-
#endif
  //->
  for (int i = 0; i < 2; ++i) {
    //Create an object in shared memory
    my_class * my_object = shmem.construct<my_class>("my_object")();
    my_class * my_object2 = shmem.construct<my_class>(anonymous_instance)();
    shmem.destroy_ptr(my_object2);

    my_deleter<my_class> d(shmem.get_segment_manager());
    BOOST_TRY{
        boost::interprocess::scoped_ptr<my_class, my_deleter<my_class> > s_ptr(my_object, d);
        //Let's emulate a exception capable operation
        //In the second try, throw an exception
        if(i == 1){
          throw(my_exception());
        }
        //If we have passed the dangerous zone
        //we can release the scoped pointer
        //to avoid destruction
        s_ptr.release();
      }
      BOOST_CATCH(const my_exception &){} BOOST_CATCH_END
  }
  return 0;
}