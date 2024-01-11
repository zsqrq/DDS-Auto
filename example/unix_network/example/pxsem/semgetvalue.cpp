//
// Created by wz on 24-1-11.
//
#include "common/unpipc.h"

int main(int argc, char** argv) {
  sem_t *sem;
  int val, flags;
  flags = O_RDWR | O_CREAT;
  val = 0;

  if (argc != 2) {
    err_quit("usage: semgetvalue <name>");
  }
  sem = Sem_open(argv[1], 0);
  Sem_getvalue(sem, &val);
  printf("value = %d\n", val);
  Sem_close(sem);
  exit(0);
}