#include <sys/select.h>
#include <sys/time.h>
/**
 * fd_set data-type a bit array
 * @disucss 0,1,2 is preserved for standard input/output/error. And the rest
 *   add one by one
 * @example
 *  fd_set allset; FD_ZERO(&allset);
 *  FD_SET(fileno(stdin), &allset); FD_SET(listenfd, &allset);
 *  client1: FD_SET(connfd, &allset);
 *  client2: FD_SET(connfd, &allset);
 *  allset = [0=>fileno(stdin), 1, 2, 3=>serv.listenfd, 4=>select1.connfd,
 *            5=>select2.connfd];
 */
typedef long int __fd_mask; 
#define __NFDBITS (8 * (int)sizeof(__fd_mask))                  // 8 * 8 = 64
#define __FD_ELT(fd) (fd / __NFDBITS)
#define __FD_MASK(fd) ((__fd_mask) 1 << (fd % __NFDBITS))
typedef struct{
#ifdef __USE_XOPEN
  __fd_maskfds_bits[__FD_SETSIZE/__NFDBITS];
#define __FDS_BITS(set) ((set)->fds_bits)
#else
  __fd_mask__fds_bits[__FD_SETSIZE/__NFDBITS];
#define __FDS_BITS(set) ((set)->__fds_bits)
#endif
} fd_set;
#define FD_SETSIZE 1024
/**
 * @param fd_set * fdset
 */
#define FD_ZERO(fdset)                                                  \
  do{                                                                   \
    unsigned int __i;                                                   \
    fd_set *__arr = (fdset);                                            \
    for(__i = 0; __i < sizeof(fd_set) / sizeof(__fd_mask); ++__i)       \
      __FDS_BITS(__arr)[__i] = 0;                                       \
  } while(0)
    
#define FD_SET(fd, fdset)     \
  ((void)(__FDS_BITS(fdset)[__FD_ELT(fd)] |= __FD_MASK(fd)))
  
#define FD_CLR(fd, fdset)     \
  ((void)(__FDS_BITS(fdset)[__FD_ELT(fd)] &= ~__FD_MASK(fd)))
  
#define FD_ISSET(fd, fdset)   \
  ((__FDS_BITS(fdset)[__FD_ELT(fd)] & __FD_MASK(fd)) != 0)


/**
 * @param int maxfd_add1 the maximum no. of fds across all the sets, plus 1
 * @param fd_set any of these args can be as a null ptr
 * @param const struct timeval *timeout wait for any of the ready descriptors
 *  NULL ptr: wait forever
 * @return >0 on ready descriptors; 0 on timeout; -1 on error
 * @discuss when a socket is ready for reading
 *  1. received buffer > SO_RCVLOWAT  low-water; return > 0;
 *  2. connection closed (e.g. received a FIN);  return 0;
 *  3. listenfd, completed connection queue is nonzero
 *  4. socket error is pending; return -1 with errno;
 * @disuss when a socket is ready for writing
 *  1. send buffer > SO_SNDLOWAT; and connected socket or UDP;  return > 0;
 *  2. connection closed; write operation generates SIGPIPE
 *  3. socket error is pending; returns -1 with errno;
 * @discuss exception condition
 *  1. the arrival of out-of-band data for a socket
 * @disucss When an error occurs, it's marked as both readable and writable
 */
struct timeval{
  long tv_sec;
  long tv_usec;   // microseconds
}; 
int select(int maxfd_add1, 
            fd_set *readset, fd_set *writeset, fd_set *exceptset,
            const struct timeval *timeout);
/**
 * @param sigmask 
 */
struct timespec{
  long tv_sec;
  long tv_nsec;   // nanoseconds
}; 
int pselect(int maxfd_add1,             
            fd_set *readset, fd_set *writeset, fd_set *exceptset,
            const struct timespec *timeout, const sigset_t *sigmask);
            
            
/**
 * +---------------------------------------------------------------------------+
 * |          |e|r|     e=events; r=revents;                                   
 * |---------------------------------------------------------------------------|
 * |POLLIN    |Y|Y| = POLLRDNORM | POLLRDBAND
 * |POLLRDNORM|Y|Y| Normal Data can be read
 * |POLLRDBAND|Y|Y| Priority Band Data can be read
 * |POLLPRI   |Y|Y| High-prio., e.g. out-of-band data
 * |---------------------------------------------------------------------------|
 * |POLLOUT   |Y|Y| = POLLWRNORM
 * |POLLWRNORM|Y|Y| Normal Data can be write
 * |POLLWRBAND|Y|Y| Priority Band Data can be written
 * |---------------------------------------------------------------------------|
 * |POLLERR   | |Y| Error has occurred
 * |POLLHUP   | |Y| Hangup has occurred
 * |POLLNVAL  | |Y| fd is not an open file
 * +---------------------------------------------------------------------------+
 * @param nfds_t unsigned long fds type
 * @param int timeout
 *  <0 | INFTIM  infinite time, wait forever
 * @return >0 fds that have a nonzero revents; 0 no fd ready; -1 on error
 * @example
 *  fds[0].fd = listenfd;
 *  fds[0].events = POLLIN | POLLOUT | POLLERR; // interest in read/write/error
 *  poll(fds, 1, INFTIM);
 *  if(fds[0].revents & (POLLRDNORM | POLLERR)) // 
 */
typedef unsigned long nfds_t; 
struct pollfd{
  int fd;
  short events;       // interest
  short revents;      // occurred
};
int poll(struct pollfd * fds, nfds_t nfds, int timeout)
            

      
            
            
            
            
            
            
            
            
            
            
            