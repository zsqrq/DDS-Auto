//
// Created by wz on 24-1-16.
//
#include "common/unpipc.h"
#define SEM_NAME "mysem"

int main(int argc, char** argv) {

  int fd, i, nloop, zero = 0;
  int *ptr;
  sem_t	*mutex;

  if (argc != 3)
    err_quit("usage:  <pathname> <#loops>");
  nloop = atoi(argv[2]);

  fd = Open(argv[1], O_RDWR | O_CREAT, FILE_MODE);
  Write(fd,&zero, sizeof(int));
  ptr = (int*)Mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd,0);
  Close(fd);

  mutex = Sem_open(SEM_NAME, O_CREAT | O_EXCL, FILE_MODE, 1);
  Sem_unlink(SEM_NAME);
  setbuf(stdout, NULL);	/* stdout is unbuffered */
  if (Fork() == 0) {		/* child */
    for (i = 0; i < nloop; i++) {
      Sem_wait(mutex);
      printf("child: %d\n", (*ptr)++);
      Sem_post(mutex);
    }
    exit(0);
  }

  /* 4parent */
  for (i = 0; i < nloop; i++) {
    Sem_wait(mutex);
    printf("parent: %d\n", (*ptr)++);
    Sem_post(mutex);
  }
  exit(0);
}