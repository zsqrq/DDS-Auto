//
// Created by wz on 24-1-9.
//

#ifndef FAST_DDS_EXAMPLE_EXAMPLE_UNIX_NETWORK_EXAMPLE_SVMSGCLISERV_MESG_RECV_H_
#define FAST_DDS_EXAMPLE_EXAMPLE_UNIX_NETWORK_EXAMPLE_SVMSGCLISERV_MESG_RECV_H_
#include "message.h"

ssize_t
mesg_recv(int id, struct mymesg *mptr)
{
  ssize_t	n;

  n = msgrcv(id, &(mptr->mesg_type), MAXMESGDATA, mptr->mesg_type, 0);
  mptr->mesg_len = n;		/* return #bytes of data */

  return(n);				/* -1 on error, 0 at EOF, else >0 */
}
/* end mesg_recv */

ssize_t
Mesg_recv(int id, struct mymesg *mptr)
{
  ssize_t	n;

  if ( (n = mesg_recv(id, mptr)) == -1)
    err_sys("mesg_recv error");
  return(n);
}

#endif //FAST_DDS_EXAMPLE_EXAMPLE_UNIX_NETWORK_EXAMPLE_SVMSGCLISERV_MESG_RECV_H_
