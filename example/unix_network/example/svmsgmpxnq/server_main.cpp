//
// Created by wz on 24-1-9.
//
#include "common/unpipc.h"
#include "svmsg.h"
#include "server.h"
#include "client.h"


int main(int argc, char **argv)
{
  int msqid;
  msqid = Msgget(MQ_KEY1, 0666 | IPC_CREAT);

  server(msqid, msqid);

  exit(0);
}
