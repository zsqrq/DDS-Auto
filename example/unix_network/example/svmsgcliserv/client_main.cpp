//
// Created by wz on 24-1-9.
//
#include "svmsg.h"
#include "client.h"
#include "server.h"
#include "message.h"

int main(int argc, char** argv) {
  int msqid;
  msqid = Msgget(MQ_KEY1, 0);

  client(msqid, msqid);

  exit(0);
}