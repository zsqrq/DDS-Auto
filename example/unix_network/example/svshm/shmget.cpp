//
// Created by wz on 24-1-17.
//
#include "common/unpipc.h"

int main(int argc, char** argv) {
  int c, id, oflag;
  char* ptr;
  size_t length;
  oflag = 0666 | IPC_CREAT;

  while ((c = getopt(argc, argv, "e")) != -1) {
    switch (c) {
      case 'e':
        oflag |= IPC_EXCL;
        break;
    }
  }
  if (optind != argc - 2)
    err_quit("usage: shmget [ -e ] <pathname> <length>");
  length = atoi(argv[optind + 1]);
  id = shmget(ftok(argv[optind], 0), length, oflag);
  ptr = (char*)shmat(id, NULL, 0);
  exit(0);
}