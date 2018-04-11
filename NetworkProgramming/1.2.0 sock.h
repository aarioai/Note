#include <sys/types.h>      // basic system data types
#include <sys/socket.h>     // basic socket definations
#include <sys/time.h>        // timeval{} for select()
#include <time.h>            // timespec{} for pselect()
#include <netinet/in.h>     // for sockaddr_in
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>            // for nonblocking
#include <netdb.h>
#include <signal.h>
#include <stdio.h>          // for printf
#include <stdlib.h>         // for exit
#include <string.h>         // for bzero()
#include <sys/stat.h>       // for S_xxx file mode constants
#include <sys/uio.h>        // for iovec{} and readv /writev
#include <unistd.h>
#include <sys/wait.h>
#include <sys/un.h>
#include <pthread.h>


#include <sys/select.h>     // for pselect()

#include <poll.h>           // for poll()
#include <limits.h>         // for poll() OPEN_MAX
#define INFTIME -1

// #define SA struct sockaddr

#define SERV_BUF_SIZE 4096 // MAXLINE, buffer size for reads and writes
#define SERV_LISTEN_QUEUES 1024 // LISTENQ 2nd arg. to listen()
#define SERV_LISTEN_PORT 9877 // any a ephemeral[ɪˈfɛmərəl] port between [5000, 49152]

#define INET_ADDR_STRLEN    16
/**
 * Passing Binary Structures
 * @note long is diff in diff host, so we can't pass value by long. Passing 
 *  binary struct instead.
 */
struct args {
  long arg1;
  long arg2;
};
struct results {
  char in_addr[INET_ADDR_STRLEN];
  char in6_addr[INET_ADDR_STRLEN];
  long sum;
};

/**
 * @note true on 1; false on 0; 0 == -1  is 0
 * @param int deprive 0 on success; 1 on error
 */
int vDebug(const char*msg, int deprive){
  if(deprive<0){
    if(errno == EINTR){
      printf("errno==EINTR\n");
      return 0;
    }
    printf("%s errno:%d(%s)\n", msg, errno, strerror(errno));
    exit(EXIT_FAILURE);
    return -1;
  }
  return 1;
}