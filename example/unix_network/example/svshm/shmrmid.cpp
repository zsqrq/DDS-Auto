//
// Created by wz on 24-1-17.
//
#include	"common/unpipc.h"

int
main(int argc, char **argv)
{
  int		id;

  if (argc != 2)
    err_quit("usage: shmrmid <pathname>");

  id = shmget(ftok(argv[1], 0), 0, SVSHM_MODE);
  shmctl(id, IPC_RMID, NULL);

  exit(0);
}