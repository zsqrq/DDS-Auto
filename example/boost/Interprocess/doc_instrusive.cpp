//
// Created by wz on 24-1-24.
//
#include "boost/interprocess/detail/workaround.hpp"
#include "boost/interprocess/managed_shared_memory.hpp"
#include "boost/interprocess/smart_ptr/intrusive_ptr.hpp"
#include "glog/logging.h"
#include "test/get_process_id_name.h"

using namespace boost::interprocess;

namespace N {
class reference_counted_class {
 private:
  reference_counted_class(const reference_counted_class&);
  reference_counted_class& operator=(const reference_counted_class&);

  using segment_manager = managed_shared_memory::segment_manager;
  unsigned int m_use_count;
  boost::interprocess::offset_ptr<segment_manager> mp_segment_manager;

 public:
  reference_counted_class(segment_manager* s_mngr)
  : m_use_count(0), mp_segment_manager(s_mngr){}

  ~reference_counted_class(){}

  unsigned int use_count() const { return m_use_count; }

  inline friend void intrusive_ptr_add_ref(reference_counted_class* p) {
    ++p->m_use_count;
  }

  inline friend void intrusive_ptr_release(reference_counted_class* p) {
    if (--p->m_use_count == 0)
      p->mp_segment_manager->destroy_ptr(p);
  }
};

}

class intrusive_ptr_owner {
  using intrusive_ptr_t = boost::interprocess::intrusive_ptr<N::reference_counted_class, offset_ptr<void>>;
  intrusive_ptr_t m_intrusive_ptr;
 public:
  intrusive_ptr_owner(N::reference_counted_class* ptr)
      : m_intrusive_ptr(ptr) {}
};

int main(int argc, char* argv[]) {
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging(argv[0]);

  //Remove shared memory on construction and destruction
  struct shm_remove {
    shm_remove() { shared_memory_object::remove("MyIntrusiveSharedMemory"); }
    ~shm_remove(){ shared_memory_object::remove("MyIntrusiveSharedMemory"); }
  } remover;
  (void) remover;

  managed_shared_memory shmem(create_only, "MyIntrusiveSharedMemory",10000);

  //Create the unique reference counted object in shared memory
  N::reference_counted_class *ref_counted =
      shmem.construct<N::reference_counted_class>("ref_counted")(shmem.get_segment_manager());
  intrusive_ptr_owner* intrusive_owner_array =
      shmem.construct<intrusive_ptr_owner>(boost::interprocess::anonymous_instance)[10](ref_counted);

  //Now test that reference count is ten
  if (ref_counted->use_count() != 10) {
    LOG(ERROR) << "ref counted is not ten";
    return 1;
  }
  LOG(INFO) << "ref counted is : " << ref_counted->use_count();

  //Now destroy the array of intrusive pointer owners
  //This should destroy every intrusive_ptr and because of
  //that reference_counted_class will be destroyed
  shmem.destroy_ptr(intrusive_owner_array);

  //Now the reference counted object should have been destroyed
  if (shmem.find<intrusive_ptr_owner>("ref_counted").first) {
    LOG(ERROR) << "Not destroy ref_counted clearly";
    return 1;
  }
  return 0;
}