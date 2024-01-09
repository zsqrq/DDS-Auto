//
// Created by wz on 24-1-9.
//
#include "common/unpipcmsg.h"
int
main(int argc, char **argv)
{
  int		mqid;

  if (argc != 2)
    err_quit("usage: msgrmid <pathname>");

  mqid = Msgget(Ftok(argv[1], 0), 0);
  Msgctl(mqid, IPC_RMID, NULL);

  exit(0);
}
