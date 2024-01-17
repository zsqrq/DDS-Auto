//
// Created by wz on 24-1-17.
//

#ifndef FAST_DDS_EXAMPLE_EXAMPLE_UNIX_NETWORK_EXAMPLE_PXSHM_CLISERV_H_
#define FAST_DDS_EXAMPLE_EXAMPLE_UNIX_NETWORK_EXAMPLE_PXSHM_CLISERV_H_

#include	"common/unpipc.h"

#define	MESGSIZE	256		/* max #bytes per message, incl. null at end */
#define	NMESG		 16		/* max #messages */

struct shmstruct {		/* struct stored in shared memory */
  sem_t	mutex;			/* three Posix memory-based semaphores */
  sem_t	nempty;
  sem_t	nstored;
  int	nput;			/* index into msgoff[] for next put */
  long	noverflow;		/* #overflows by senders */
  sem_t	noverflowmutex;	/* mutex for noverflow counter */
  long	msgoff[NMESG];	/* offset in shared memory of each message */
  char	msgdata[NMESG * MESGSIZE];	/* the actual messages */
};


#endif //FAST_DDS_EXAMPLE_EXAMPLE_UNIX_NETWORK_EXAMPLE_PXSHM_CLISERV_H_
