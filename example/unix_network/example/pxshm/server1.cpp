//
// Created by wz on 24-1-17.
//
#include "common/unpipc.h"

struct shmstruct {
  int count;
};

sem_t *mutex;

int main(int argc, char** argv) {
  int fd;
  struct shmstruct *ptr;
  if (argc != 3)
    err_quit("usage: server1 <shmname> <semname>");

  shm_unlink(argv[1]);
  fd = shm_open(argv[1], O_RDWR | O_CREAT | O_EXCL, FILE_MODE);
  ftruncate(fd, sizeof(struct shmstruct));
  ptr = static_cast<struct shmstruct*>(mmap(NULL, sizeof(struct shmstruct),
      PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
  Close(fd);
  sem_unlink(argv[2]);
  mutex = sem_open(argv[2], O_CREAT | O_EXCL, FILE_MODE, 1);
  sem_close(mutex);
  exit(0);
}