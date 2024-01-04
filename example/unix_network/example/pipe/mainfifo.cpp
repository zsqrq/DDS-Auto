//
// Created by wz on 24-1-3.
//

#include "common/unpipc.h"

#define FIFO1 "/tmp/fifo.1"
#define FIFO2 "/tmp/fifo.2"

void Client(int readfd, int writefd) {
  size_t len;
  ssize_t n;
  char buf[MAXLINE];

  Fgets(buf, MAXLINE, stdin);
  len = strlen(buf);

  if (buf[len-1] == '\n') len--;

  Write(writefd, buf, len);
  while ((n = Read(readfd, buf, MAXLINE)) > 0) {
    Write(STDOUT_FILENO, buf, n);
  }
}
void Server(int readfd, int writefd)
{
  int		fd;
  ssize_t	n;
  char	buff[MAXLINE+1];

  /* 4read pathname from IPC channel */
  if ( (n = Read(readfd, buff, MAXLINE)) == 0)
    err_quit("end-of-file while reading pathname");
  buff[n] = '\0';		/* null terminate pathname */

  if ( (fd = open(buff, O_RDONLY)) < 0) {
    /* 4error: must tell client */
    snprintf(buff + n, sizeof(buff) - n, ": can't open, %s\n",
             strerror(errno));
    n = strlen(buff);
    Write(writefd, buff, n);

  } else {
    /* 4open succeeded: copy file to IPC channel */
    while ( (n = Read(fd, buff, MAXLINE)) > 0)
      Write(writefd, buff, n);
    Close(fd);
  }
}

int main(int argc, char** argv) {
  int readfd, writefd;
  pid_t  childpid;

  if ((mkfifo(FIFO1, FILE_MODE) < 0) && (errno != EEXIST)) {
    err_sys("can't create %s", FIFO1);
  }
  if ((mkfifo(FIFO2, FILE_MODE) < 0) && (errno != EEXIST)) {
    unlink(FIFO1);
    err_sys("can't create %s", FIFO2);
  }

  if ((childpid = Fork()) == 0) {
    readfd = Open(FIFO1, O_RDONLY, 0);
    writefd = Open(FIFO2, O_WRONLY, 0);

    Server(readfd, writefd);
    exit(0);
  }

  writefd = Open(FIFO1, O_WRONLY, 0);
  readfd = Open(FIFO2, O_RDONLY, 0);
  Client(readfd, writefd);
  Waitpid(childpid, NULL, 0);
  Close(readfd);
  Close(writefd);

  Unlink(FIFO1);
  Unlink(FIFO2);

  exit(0);
}
