//
// Created by wz on 24-1-3.
//
#include "common/unpipc.h"
#include "client.h"
#include "server.h"

#define	FIFO1	"/tmp/fifo.1"
#define	FIFO2	"/tmp/fifo.2"
int main(int argc, char **argv)
{
  int		readfd, writefd;
  pid_t	childpid;

  /* 4Create two FIFOs; OK if they already exist */
  if ((mkfifo(FIFO1, FILE_MODE) < 0) && (errno != EEXIST))
    err_sys("can't create %s", FIFO1);
  if ((mkfifo(FIFO2, FILE_MODE) < 0) && (errno != EEXIST)) {
    unlink(FIFO1);
    err_sys("can't create %s", FIFO2);
  }

  if ( (childpid = Fork()) > 0) {		/* parent */
    writefd = Open(FIFO1, O_WRONLY, 0);
    readfd = Open(FIFO2, O_RDONLY, 0);

    client(readfd, writefd);

    Waitpid(childpid, NULL, 0);		/* wait for child to terminate */

    Close(readfd);
    Close(writefd);

    Unlink(FIFO1);
    Unlink(FIFO2);
    exit(0);

  }
  /* 4child */
  readfd = Open(FIFO1, O_RDONLY, 0);
  writefd = Open(FIFO2, O_WRONLY, 0);

  server(readfd, writefd);
  exit(0);
}
