//
// Created by wz on 24-1-5.
//
#include "common/unpipc.h"

mqd_t mqd;
void* buff;
struct mq_attr attr;
struct sigevent sigev;

static void sig_usr1(int signo) {
  ssize_t n;
  Mq_notify(mqd, &sigev);
  n = Mq_receive(mqd, (char*)buff, attr.mq_msgsize, NULL);
  printf("SIGUSR1 received, read %ld bytes\n", (long) n);
  return;
}

int main(int argc, char** argv) {

  if (argc != 2) {
    err_quit("usage: mqnotifysig1 <name>");
  }
  mqd = Mq_open(argv[1], O_RDONLY);
  Mq_getattr(mqd, &attr);
  buff = Malloc(attr.mq_msgsize);

  signal(SIGUSR1, sig_usr1);
  sigev.sigev_notify = SIGEV_SIGNAL;
  sigev.sigev_signo = SIGUSR1;
  Mq_notify(mqd, &sigev);

  for (;;) { pause();}
  exit(0);
}

