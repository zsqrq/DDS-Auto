//
// Created by wz on 24-1-10.
//

#ifndef FAST_DDS_EXAMPLE_EXAMPLE_UNIX_NETWORK_EXAMPLE_LOCK_LOCKFCNTL_H_
#define FAST_DDS_EXAMPLE_EXAMPLE_UNIX_NETWORK_EXAMPLE_LOCK_LOCKFCNTL_H_

#include "common/unpipc.h"
#include <fcntl.h>
#include <stdio.h>


void my_lock(int fd) {
  struct flock lock;
  lock.l_type = F_WRLCK;
  lock.l_whence = SEEK_SET;
  lock.l_start = 0;
  lock.l_len = 0;				/* write lock entire file */

  Fcntl(fd, F_SETLKW, &lock);
}

void
my_unlock(int fd)
{
  struct flock	lock;

  lock.l_type = F_UNLCK;
  lock.l_whence = SEEK_SET;
  lock.l_start = 0;
  lock.l_len = 0;				/* unlock entire file */

  Fcntl(fd, F_SETLK, &lock);
}


#endif //FAST_DDS_EXAMPLE_EXAMPLE_UNIX_NETWORK_EXAMPLE_LOCK_LOCKFCNTL_H_
