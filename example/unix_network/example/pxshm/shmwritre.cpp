//
// Created by wz on 24-1-17.
//
#include "common/unpipc.h"

int main(int argc, char** argv) {
  int		i, fd;
  struct stat	stat;
  unsigned char	*ptr;

  if (argc != 2)
    err_quit("usage: shmwrite <name>");

  fd = Shm_open(argv[1], O_CREAT | O_RDWR, FILE_MODE);
  Fstat(fd, &stat);
  ptr = (unsigned char*) Mmap(NULL, stat.st_size, PROT_READ | PROT_WRITE,
                              MAP_SHARED, fd, 0);
  Close(fd);

  for (i = 0; i < stat.st_size; ++i) {
    *ptr++ = i % 256;
  }
  exit(0);
}