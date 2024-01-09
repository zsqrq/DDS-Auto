//
// Created by wz on 24-1-9.
//
#include "common/unpipc.h"
#include "svmsg.h"
#include "server.h"
#include "client.h"


int main(int argc, char **argv)
{
  int		readid, writeid;

  readid = Msgget(MQ_KEY1, 0666 | IPC_CREAT);
  writeid = Msgget(MQ_KEY2, 0666 | IPC_CREAT);

  server(readid, writeid);

  exit(0);
}
