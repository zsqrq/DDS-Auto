//
// Created by wz on 24-1-26.
//
#include "boost/interprocess/detail/workaround.hpp"
#include "boost/interprocess/managed_mapped_file.hpp"
#include "boost/interprocess/smart_ptr/shared_ptr.hpp"
#include "boost/interprocess/smart_ptr/weak_ptr.hpp"
#include "test/get_process_id_name.h"
#include "glog/logging.h"
#include <cassert>

using namespace boost::interprocess;

//This is type of the object we want to share
struct type_to_share
{};

//This is the type of a shared pointer to the previous type
//that will be built in the mapped file
typedef managed_shared_ptr<type_to_share, managed_mapped_file>::type shared_ptr_type;
typedef managed_weak_ptr<type_to_share, managed_mapped_file>::type   weak_ptr_type;

//This is a type holding a shared pointer
struct shared_ptr_owner {
  shared_ptr_type shared_ptr_;
  shared_ptr_owner(const shared_ptr_type& other_owner)
      : shared_ptr_(other_owner){}

  shared_ptr_owner(const shared_ptr_owner& other_owner)
      : shared_ptr_(other_owner.shared_ptr_) {}
};

int main(int argc, char *argv[]) {
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging(argv[0]);

#if 1
  std::string mapped_file(boost::interprocess::ipcdetail::get_temporary_path());
  mapped_file += "/"; mapped_file += test::get_process_id_name();
  const char *MappedFile = mapped_file.c_str();
#else
  //->
   const char *MappedFile  = "MyMappedFile";
   //<-
#endif

  struct file_remove {
    const char* MappedFile_;
    file_remove(const char* MappedFile)
        : MappedFile_(MappedFile) {
      file_mapping::remove(MappedFile_);
    }
  }remover(MappedFile);

  {
    managed_mapped_file file(create_only, MappedFile, 65536);
    shared_ptr_type local_shared_ptr =
        make_managed_shared_ptr(file.construct<type_to_share>("object to share")(),file);
    LOG(INFO) << "Local shared pointer used1 : " << local_shared_ptr.use_count();

    shared_ptr_owner* owner1 = file.construct<shared_ptr_owner>("owner1")(local_shared_ptr);
    LOG(INFO) << "Local shared pointer used2 : " << local_shared_ptr.use_count();

    //local_shared_ptr releases object ownership
    local_shared_ptr.reset();
    LOG(INFO) << "Local shared pointer used after release : " << local_shared_ptr.use_count();
    LOG(INFO) << "Owner shared pointer used after release : " << owner1->shared_ptr_.use_count();

    shared_ptr_owner* owner2 = file.construct<shared_ptr_owner>("owner2")(*owner1);
    assert(owner1->shared_ptr_.use_count() == 2);
    assert(owner2->shared_ptr_.use_count() == 2);
    assert(owner1->shared_ptr_.get() == owner2->shared_ptr_.get());
    //<-
    (void)owner2;
  }

  {
    //Reopen the mapped file and find again all owners
    managed_mapped_file file(open_only, MappedFile);
    shared_ptr_owner *owner1 = file.find<shared_ptr_owner>("owner1").first;
    shared_ptr_owner *owner2 = file.find<shared_ptr_owner>("owner2").first;
    assert(owner1 && owner2);
    //Check everything is as expected
    assert(file.find<type_to_share>("object to share").first != 0);
    assert(owner1->shared_ptr_.use_count() == 2);
    assert(owner2->shared_ptr_.use_count() == 2);
    assert(owner1->shared_ptr_.get() == owner2->shared_ptr_.get());

    file.destroy_ptr(owner1);
    assert(owner1->shared_ptr_.use_count() == 2);
    assert(owner2->shared_ptr_.use_count() == 2);
    assert(owner1->shared_ptr_.get() == owner2->shared_ptr_.get());

    //Now destroy one of the owners, the reference count drops.
    file.destroy_ptr(owner1);
    assert(owner2->shared_ptr_.use_count() == 1);

    weak_ptr_type local_observer1(owner2->shared_ptr_);
    assert(local_observer1.use_count() == owner2->shared_ptr_.use_count());

    {  //Create a local shared pointer from the weak pointer
      shared_ptr_type local_shared_ptr = local_observer1.lock();
      assert(local_observer1.use_count() == owner2->shared_ptr_.use_count());
      assert(local_observer1.use_count() == 2);
    }

    //Now destroy the remaining owner. "object to share" will be destroyed
    file.destroy_ptr(owner2);
    assert(file.find<type_to_share>("object to share").first == 0);

    //Test observer
    assert(local_observer1.expired());
    assert(local_observer1.use_count() == 0);

  }
  return 0;
}