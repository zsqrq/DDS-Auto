//
// Created by wz on 24-1-16.
//
#include "common/unpipc.h"

#define SEM_NAME "mysem"

int count = 0;

int main(int argc, char** argv) {
  int i, nloop;
  sem_t *mutex;
  if (argc != 2)
    err_quit("usage: incr1 <#loops>");
  nloop = atoi(argv[1]);

  mutex = sem_open("/home/wz/docker/mysem",  O_CREAT,
                   S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH, 1);
  sem_unlink(Px_ipc_name(SEM_NAME));

  setbuf(stdout, NULL);
  if (Fork() == 1) {
    for (int i =0; i < nloop; ++i) {
      sem_wait(mutex);
      printf("child: %d\n", count++);
      sem_post(mutex);
    }
    exit(0);
  }

  for (i = 0; i < nloop;++i) {
    sem_wait(mutex);
    printf("parent: %d\n", count++);
    sem_post(mutex);
  }
  exit(0);
}