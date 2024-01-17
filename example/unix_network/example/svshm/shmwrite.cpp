//
// Created by wz on 24-1-17.
//
#include	"common/unpipc.h"

int
main(int argc, char **argv)
{
  int		i, id;
  struct shmid_ds	buff;
  unsigned char	*ptr;

  if (argc != 2)
    err_quit("usage: shmwrite <pathname>");

  id = shmget(ftok(argv[1], 0), 0, 0666);
  ptr = (unsigned char *)shmat(id, NULL, 0);
  shmctl(id, IPC_STAT, &buff);

  /* 4set: ptr[0] = 0, ptr[1] = 1, etc. */
  for (i = 0; i < buff.shm_segsz; i++)
    *ptr++ = i % 256;

  exit(0);
}