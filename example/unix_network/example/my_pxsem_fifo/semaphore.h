//
// Created by wz on 24-1-12.
//

#ifndef FAST_DDS_EXAMPLE_EXAMPLE_UNIX_NETWORK_EXAMPLE_MY_PXSEM_FIFO_SEMAPHORE_H_
#define FAST_DDS_EXAMPLE_EXAMPLE_UNIX_NETWORK_EXAMPLE_MY_PXSEM_FIFO_SEMAPHORE_H_

typedef struct {
  int	sem_fd[2];	/* two fds: [0] for reading, [1] for writing */
  int	sem_magic;	/* magic number if open */
} mysem_t;

#define	SEM_MAGIC	0x89674523

#ifdef	SEM_FAILED
#undef	SEM_FAILED
#define	SEM_FAILED	((mysem_t *)(-1))	/* avoid compiler warnings */
#endif
/* end semaphoreh */

/* 4our functions */
int		 mysem_close(mysem_t *);
mysem_t	*mysem_open(const char *, int, ... );
int		 mysem_post(mysem_t *);
int		 mysem_unlink(const char *);
int		 mysem_wait(mysem_t *);

/* 4and the corresponding wrapper functions */
void	 Mysem_close(mysem_t *);
mysem_t	*Mysem_open(const char *, int, ... );
void	 Mysem_post(mysem_t *);
void	 Mysem_unlink(const char *);
void	 Mysem_wait(mysem_t *);

#endif //FAST_DDS_EXAMPLE_EXAMPLE_UNIX_NETWORK_EXAMPLE_MY_PXSEM_FIFO_SEMAPHORE_H_
