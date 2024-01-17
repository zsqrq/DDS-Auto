//
// Created by wz on 24-1-17.
//
#include	"common/unpipc.h"
int
main(int argc, char **argv)
{
  int		i, id;
  struct shmid_ds	buff;
  unsigned char	c, *ptr;

  if (argc != 2)
    err_quit("usage: shmread <pathname>");

  id = shmget(ftok(argv[1], 0), 0, 0666);
  ptr = (unsigned char *)shmat(id, NULL, 0);
  shmctl(id, IPC_STAT, &buff);

  /* 4check that ptr[0] = 0, ptr[1] = 1, etc. */
  for (i = 0; i < buff.shm_segsz; i++)
    printf("ptr[%d] is : %s",i,*ptr);
    if ( (c = *ptr++) != (i % 256))
      err_ret("ptr[%d] = %d", i, c);

  exit(0);
}