//
// Created by wz on 24-1-9.
//

#ifndef FAST_DDS_EXAMPLE_EXAMPLE_UNIX_NETWORK_EXAMPLE_SVMSGCLISERV_MESG_SEND_H_
#define FAST_DDS_EXAMPLE_EXAMPLE_UNIX_NETWORK_EXAMPLE_SVMSGCLISERV_MESG_SEND_H_
#include "message.h"

ssize_t
mesg_send(int id, struct mymesg *mptr)
{
  return(msgsnd(id, &(mptr->mesg_type), mptr->mesg_len, 0));
}
/* end mesg_send */

void
Mesg_send(int id, struct mymesg *mptr)
{
  ssize_t	n;

  if ( (n = msgsnd(id, &(mptr->mesg_type), mptr->mesg_len, 0)) == -1)
    err_sys("mesg_send error");
}

#endif //FAST_DDS_EXAMPLE_EXAMPLE_UNIX_NETWORK_EXAMPLE_SVMSGCLISERV_MESG_SEND_H_
