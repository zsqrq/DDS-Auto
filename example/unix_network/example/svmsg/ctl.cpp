//
// Created by wz on 24-1-9.
//
#include "common/unpipc.h"

int main(int argc, char** argv) {
  int msqid;
  struct msqid_ds info;
  struct msgbuf buf;

  msqid = Msgget(IPC_PRIVATE, 0666 | IPC_CREAT);

  buf.mtype = 1;
  buf.mtext[0] = 1;
  Msgsnd(msqid, &buf, 1, 0);
  Msgctl(msqid, IPC_STAT, &info);
  printf("read-write: %03o, cbytes = %lu, qnum = %lu, qbytes = %lu\n",
         info.msg_perm.mode & 0777, (unsigned long ) info.msg_cbytes,
         (unsigned long ) info.msg_qnum, (unsigned long ) info.msg_qbytes);
  system("ipcs -q");

  Msgctl(msqid, IPC_RMID, NULL);
  exit(0);
}