//
// Created by wz on 24-1-9.
//
#include "common/unpipcmsg.h"

int main(int argc, char** argv) {

  int		c, oflag, mqid;

  oflag = 0666 | IPC_CREAT;
  while ( (c = Getopt(argc, argv, "e")) != -1) {
    switch (c) {
      case 'e':
        oflag |= IPC_EXCL;
        break;
    }
  }
  if (optind != argc - 1)
    err_quit("usage: msgcreate [ -e ] <pathname>");

  mqid = Msgget(Ftok(argv[optind], 0), oflag);
//  mqid = Msgget(IPC_PRIVATE, oflag);
  exit(0);

}