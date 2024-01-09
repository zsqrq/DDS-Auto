//
// Created by wz on 24-1-9.
//
#include "svmsg.h"
#include "client.h"
#include "server.h"
#include "message.h"

int main(int argc, char** argv) {
  int readid, writeid;
  writeid = Msgget(MQ_KEY1, NULL);
  readid = Msgget(MQ_KEY2, NULL);

  client(readid, writeid);
  Msgctl(readid, IPC_RMID,  NULL);
  Msgctl(writeid, IPC_RMID, NULL);

  exit(0);
}