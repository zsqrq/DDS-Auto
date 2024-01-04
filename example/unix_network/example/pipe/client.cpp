//
// Created by wz on 24-1-1.
//
#include "common/unpipc.h"

void client(int readfd, int writefd) {
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
