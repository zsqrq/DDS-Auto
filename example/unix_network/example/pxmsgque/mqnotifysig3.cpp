//
// Created by wz on 24-1-5.
//
#include "common/unpipc.h"

volatile sig_atomic_t mq_flag;

static void sig_usr1(int);

int main(int argc, char** argv) {
  mqd_t mqd;
  void* buff;
  ssize_t n;
  sigset_t zeromask, newmask, oldmask;

  struct mq_attr attr;
  struct sigevent sigev;

  if (argc != 2) {
    err_quit("usage: mqnotifysig3 <name>");
  }
  mqd = Mq_open(argv[1], O_RDONLY | O_NONBLOCK);
  Mq_getattr(mqd, &attr);
  buff = Malloc(attr.mq_msgsize);

  Sigemptyset(&zeromask);		/* no signals blocked */
  Sigemptyset(&newmask);
  Sigemptyset(&oldmask);
  Sigaddset(&newmask, SIGUSR1);
  /* 4establish signal handler, enable notification */
  Signal(SIGUSR1, sig_usr1);
  sigev.sigev_notify = SIGEV_SIGNAL;
  sigev.sigev_signo = SIGUSR1;
  Mq_notify(mqd, &sigev);

  for (;;) {
    Sigprocmask(SIG_BLOCK, &newmask, &oldmask);
    while (mq_flag == 0) {
      sigsuspend(&zeromask);
    }
    mq_flag = 0;
    Mq_notify(mqd, &sigev);
    while ((n = mq_receive(mqd, (char*)buff, attr.mq_msgsize, NULL)) >= 0) {
      printf("read %ld bytes\n", (long) n);
    }
    if (errno != EAGAIN) {
      err_sys("mq_receive error");
    }
    Sigprocmask(SIG_UNBLOCK, &newmask, NULL);
  }
  exit(0);
}

static void sig_usr1(int signo) {
  mq_flag = 1;
  return;
}