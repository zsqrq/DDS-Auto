//
// Created by wz on 24-1-4.
//
#include "mesg.h"

ssize_t mesg_send(int fd, struct mymesg* mptr) {
  return (write(fd, mptr, MESGHDRSIZE + mptr->mesg_len));
}

void Mesg_send(int fd, struct mymesg* mptr) {
  ssize_t n;
  if ((n = mesg_send(fd,mptr)) != mptr->mesg_len) {
    err_quit("mesg_send error");
  }
}