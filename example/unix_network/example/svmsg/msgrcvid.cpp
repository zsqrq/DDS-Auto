//
// Created by wz on 24-1-9.
//
#include "common/unpipcmsg.h"

#define MAXMSG (8192 + sizeof(long))

int main(int argc, char** argv) {
  int mqid;
  ssize_t n;
  struct msgbuf *buff;

  if (argc != 2) {
    err_quit("usage : msgrcvid <mqid>");
  }
  mqid = atoi(argv[1]);
  buff = static_cast<struct msgbuf*>(Malloc(MAXMSG));

  n = Msgrcv(mqid, buff, MAXMSG, 0, 0);
  printf("read %d bytes, type = %ld\n", n, buff->mtype);

  exit(0);
}