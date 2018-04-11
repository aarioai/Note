/**
 * INADDR_ANY is a wildcard IP addr. to the server
 */
INADDR_ANY 

/**
 * Since we don't know whether the socket addr. is IPv4(sockaddr_in) or 
 *  IPv6(sockaddr_in6), we use sockaddr_storage
 */
#include <netinet/in.h>
struct sockaddr_storage{
  uint8_t     ss_len;
  sa_family_t ss_family;
} 

#include <sys/socket.h>
struct sockaddr{
  uint8_t     sa_len;
  sa_family_t sa_family;      // u_int, enumeration of AaronAddrFamily
  char        sa_data[14];    // 
};
/*********************** IPv4 *************************************************/
#include <netinet/in.h>
struct in_addr {
  in_addr_t s_addr;               // uint32_t
};
struct sockaddr_in{
  uint8_t         sin_len;
  sa_family_t     sin_family;     // u_int, AF_INET
  in_port_t       sin_port;       // uint16_t 
  struct in_addr  sin_addr;       // uint32_t
  char            sin_zero[8];    // unused
};
/*********************** IPv6 *************************************************/
struct in6_addr{
  uint8_t   s6_addr[16];          // network byte ordered 128-bit IPv6 addr.
};
struct sockaddr_in6{
  uint8_t         sin6_len;       // length of this struct (28)
  sa_family_t     sin6_family;    // AF_INET6
  in_port_t       sin6_port;      // 16bit
  uint32_t        sin6_flowinfo;  // 32bit
  struct in6_addr sin6_addr;      // 128bit
  uint32_t        sin6_scope_id;  // 32bit
};

/*********************** Unix *************************************************
 * POSIX renames the Unix domain protocols as "Local IPC(interprocess communication)"
 *  
 */
#include <sys/un.h>
# define SUN_LEN(ptr) ((size_t) (((struct sockaddr_un *) 0)->sun_path) + strlen ((ptr)->sun_path))
struct sockaddr_un{
  sa_family_t sun_familty;    // AF_LOCAL
  /**
   * @var char sun_path[108] null-terminated path
   * @note if sun_path[0] that the Unix domain equivalent of the IPv4 INADDR_ANY
   *  and the IPv6 IN6ADDR_ANY_INIT constant
   */
  char sun_path[108];
};
/*******************************************************************************
 * 
 */
#include <net/if_dl.h>
struct sockaddr_dl{         // socket data link
  uint8_t     sdl_len;
  sa_family_t sdl_family;   // AF_LINK
  uint16_t    sdl_index;    // system assigned index
  uint8_t     sdl_type;     // IFT_ETHER
  uint8_t     sdl_nlen;     // interface name length, starting in sdl_data[0]
  uint8_t     sdl_alen;     // link-layer addr len
  uint8_t     sdl_slen;     // selector len
  char        sdl_data[12]; // contains interface name and link-layer addr.
};
#define LLADDR(s) ((caddr_t)(s->sdl_data + s->sdl_nlen)) 
/******************************************************************************/

/**
 * @param int fam
 *  AF_INET     // IPv4, 32bit IP + 16bit Port   
 *  AF_INET6    // IPv6  
 *  AF_LOCAL    // AF_UNIX(the historial Unix name) absolute path
 *  AF_ROUTE    // Routing sockets, sa_family = AF_LINK
 *  AF_KEY      // Key socket
 * @param int socktype
 *  SOCK_STREAM     // stream TCP  
 *  SOCK_DGRAM      // datagram UDP 
 *  SOCK_SEQPACKET  // sequenced packet SCTP
 *  SOCK_RAW        // raw
 * @param int ip_protocol_type
 *  IPPROTO_TCP
 *  IPPROTO_UDP
 *  IPPROTO_SCTP
 * @return int sockfd
 */
int socket(int fam, int socktype, int ip_protocol_type)

/**
 * assign a local protocol address to a socket.
 * @return integer 0=success; -1=error;
 */
int bind(int sockfd, const struct sockaddr* addr, socklen_t addr_len)

        


/**
 * be called by TCP server.
 * status change: CLOSED --> LISTEN(passive open)
 * max_listen_queues = incomplete_connection_queues + completed_connection_queues
 *      received: SYN j, MSS=536 ..
 *  incomplete_connection_queues (SYN_RCVD state):  have a time out of 75s
 *      send:    SYN k, ACK j+1, MSS=1460 ...
 *      RTT: about 187ms
 *      received: ACK k+1 ...
 *  completed_connection_queues (ESTABLISHED state): 3-way handshake completed
 * When the process calls accept(), the first entry on the completed queue is 
 *  returned to the process, or if the queue is empty, the process is put to
 *  sleep until an entry is placed onto the completed queue.
 * @param int max_listen_queues 
 *  It is multiplied by 1.5 in MacOS and added 3 in Linux.
 *  e.g. listen(listenfd, 2048) --> 3072 queues in MacOS and 2051 queues in Linux
 *  Provide enough number of queues for SYN flooding.
 * If the queues are full when a client SYN arrives, TCP ignores the arriving SYN;
 *  it does not send an RST. The client TCP'll retransmit its SYN, hopefully 
 *  finding room on the queue in the near future.
 * If the server responded with an RST, the client's connect() would return an
 *  error.
 */
int listen(int bindfd, int max_listen_queues)

/**
 * be used by a TCP client to establish a connection with a TCP server
 * status change: SYN_SENT(active open)
 * @notice When connect() a nonblocking socket to a different server, and the
 *  connection can't be established immediately. connect() returns immediately 
 *  with an errno EINPROGRESS but the TCP three-way handshake continues.
 * @notice nonblocking connect() is useful:
 *  1. A connect() takes one RTT
 *  2. Setting multiple connection()s
 *  3. 
 */
int connect(int sockfd, const struct sockaddr*serv_addr, socklen_t addrlen)

/**
 * When a process is blocked in "slow system call"(will ever return, like 
 *  for(;;) and read()) and the process catches a signal and the signal handler
 *  returns, the system call can return EINTR(interrupted system call).
 * @param cli_addr is used to return the protocol addr. of the connected peer
 *  process (the client).
 * @param addrlen is a value-result arg.
 *  value: sizeof(cli_addr)
 *  result: actual number of bytes stored by the kernel in the socket addr. structure
 * @return integer connected socket file descriptor 
 *  (for which the TCP three-way handshake completeds)
 */
int accept(int listenfd, struct sockaddr* cli_addr, socklen_t addrlen)


int close(int fd)
/**
 * @param int how
 *  0 SHUT_RD stop reading data; reject it when further data arrives
 *  1 SHUT_WR stop writing data;contents of socket send buffer sent to other end
 *    followed by FIN. discard any data waiting to be sent; stop looking for 
 *    ACK of data already sent
 *  2 SHUT_RDWR is equivalent to call shutdown() twice: with SHUT_RD and SHUT_WR
 */
int shutdown(int listenfd, int how)


/**
 * +---------------------------------------------------------------------------+
 * |                    |    fd(s)    |      optional
 * |---------------------------------------------------------------------------+
 * | read() write()     | any one     |  
 * | readv() writev()   | any more    |
 * | recv() send()      | sockfd one  | flags
 * | recvfrom() sendto()| sockfd one  | flags/peer addr
 * | recvmsg() sendmsg()| sockfd more | flags/peer addr/control info
 * +---------------------------------------------------------------------------+
 */

/**
 * Receive a msg. from a connection-mode or connectionless-mode socket. It is 
 *  normally used with connectionless-mode sockets because it permits the 
 *  application to retrieve the source address of received data.
 * @param int flags 
 *  MSG_DONTROUTE only for sendto(); tell the kernel that the destination is on
 *    a local attached network and not to perform a lookup of the routing table
 *    setsockopt(sockfd, SO_DONTROUTE ...) is for all operation
 *  MSG_DONTWAIT nonblocking
 *  MSG_OOB out-of-band data
 *  MSG_PEEK only for recvfrom()
 *  MSG_WAITALL only for recvfrom()
 * @return >=0 on success, bytes received; -1 on error
 */
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                 struct sockaddr *from, socklen_t *addrlen)
ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
               const struct sockaddr *sendto, socklen_t addrlen)  
/**
 * recvfrom(int sockfd, void *buf, size_t len, int flags, NULL, 0)
 */               
ssize_t recv(int sockfd, void *buf, size_t len, int flags)
ssize_t send(int sockfd, const void *buf, size_t len, int flags)


#include <sys/uio.h>
/**
 * @example
 *  char involve[] = "INVOLVE";
 *  const char *obsess = "OBSESS";
 *  struct args arg = {.arg1 = 1, .arg2 = 300};
 *  struct iovec io_vec[3];
 *  io_vec[0].iov_base = involve;
 *  io_vec[0].iov_len = strlen(involve);
 *  io_vec[1].iov_base = obsess;
 *  io_vec[1].iov_len = strlen(obsess);
 *  io_vec[2].iov_base = arg;
 *  io_vec[2].iov_len = sizeof(arg);
 *  struct msghdr msg_header;
 *  msg_header.msg_iov = io_vec;
 *  msg_header.msg_iovlen = 3;
 */
struct iovec{
  void *iov_base;   // starting address
  size_t iov_len;   // size of transfered buffer
};

struct cmsghdr{   // cmsg header
  socklen_t cmsg_len;
  /**
   * @var cmsg_level {cmsg_type}
   *  IPPROTO_IP for protocol IPv4
   *    IP_RECVDSTADDR receive destination addr. with UDP datagram
   *    IP_RECVIF receive interface index with UDP datagram
   *  IPPROTO_IPV6
   *    IPV6_DSTOPTS specify destination options
   *    IPV6_HOPLIMIT
   *    IPV6_NEXTHOP
   *    IPV6_PKTINFO
   *    IPV6_RTHDR
   *    IPV6_TCLASS
   *  SOL_SOCKET for unix domain
   *    SCM_RIGHTS  send/receive descriptors
   *    SCM_CREDS send/receive user credentials
   */
  int cmsg_level;
  int cmsg_type;
};
struct msghdr{        // msg header
  /**
   * @var void *msg_name NULL pointer on a TCP socket or a connected UDP socket;
   *  a ptr to a socket address structure on a unconnected UDP socket
   */
  void      *msg_name;
  socklen_t  msg_namelen;
  /**
   * Specify the array of input or output buffers
   */
  struct     iovec *msg_iov;  // iovec{}s
  int        msg_iovlen;
  /**
   * Speicify the location and size of the optional ancillary[æn'sɪlərɪ] data.
   *  e.g. cmsghdr{}
   * @example a Unix domain socket for descriptor passing
   *  cmsghdr{
   *    .cmsg_len = 16,
   *    .cmsg_level = SOL_SOCKET,
   *    .cmsg_type = SCM_RIGHTS,
   *  }
   *  -------------PADDING----------
   *  cmsg_data[]
   *  -------------PADDING----------
   * @example send an int fd by msg_control
   *  int fd;
   *  struct msghdr msg_hdr;
   *  char cmsg_data[CMSG_SPACE(sizeof(fd))];
   *  struct cmsghdr *cmsg_hdr;
   *  msg_hdr.msg_control = cmsg_data;
   *  msg_hdr.msg_controllen = CMSG_SPACE(sizeof(fd));    // sizeof(int)
   *  struct cmsghdr *cmsg;
   *  cmsg = CMSG_FIRSTHDR(&msg_hdr);
   *  cmsg->cmsg_len = CMSG_LEN(sizeof(fd));
   *  cmsg->cmsg_level = SOL_SOCKET;
   *  cmsg->cmsg_type = SCM_RIGHTS;
   *  *((int *)CMSG_DATA(cmsg_hdr)) = fd;
   *  sendmsg(fd, &msg_hdr, 0);
   * @example receive an int fd
   *  union {
   *    struct cmsghdr cmsg_header;                     //  cmsghdr
   *    // char cmsg_data[CMSG_ALIGN(sizeof(fd))];      // cmsg_data[]
   *    char controlPadding[CMSG_SPACE(sizeof(fd))];
   *  } control_union;
   *  struct msghdr msg_header;
   *  msg_header.control = control_union.controlPadding;
   *  msg_header.controllen = CMSG_SPACE(sizeof(fd));
   *  struct cmsghdr cmsg;
   *  recvmsg(unixfd, &msg_header, 0);
   *  if(NULL != (cmsg = *(CMSG_FIRSTHDR(&msg_header)) &&
   *      cmsg.cmsg_len == CMSG_LEN(sizeof(fd))
   *  ){
   *    int cmsg_lvl_ = cmsg.cmsg_level;
   *    int cmsg_type_ = cmsg.cmsg_type;
   *    int fd = *((int *)CMSG_DATA(&cmsg));
   *  }
   */
  void      *msg_control;
  socklen_t  msg_controllen;
  int        msg_flags;
};
// followed by unsigned char cmsg_data[], e.g. fd



#define CMSG_FIRSTHDR(msg_hdr)                                              \
  ((size_t)msg_hdr->msg_controllen >= sizeof(struct cmsghdr)                \
  ? (struct cmsghdr *)msg_hdr->msg_control : (struct *cmsghdr *)0)
#define CMSG_NXTHDR(msg_hdr,cmsg_hdr) __cmsg_nxthdr(msg_hdr, cmsg_hdr)
/**
 * @return a ptr to the first byte of data
 */
#define CMSG_ALIGN(len) ((len + sizeof(size_t) - 1) & (size_t)~(sizeof(size_t) -1)) 
#define CMSG_DATA(cmsg_hdr) ((unsigned char *)((struct cmsghdr *)cmsg_hdr + 1))
#define CMSG_LEN(len) (CMSG_ALIGN(sizeof(struct cmsghdr)) + len)
#define CMSG_SPACE(len) ((CMSG_ALIGN(len) + CMSG_ALIGN(sizeof(struct cmsghdr)))



ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags)
ssize_t sendmsg(int sockfd, struct msghdr *msg, int flags)

/**
 * Credentials
 * @example
 *  struct msghdr msg_header;
 *  struct cmsghdr cmsg_header;
 *  char control_padding[CMSG_SPACE(sizeof(struct cmsgcred))];
 *  msg_header.control = control_padding;
 *  msg_header.controllen = CMSG_SPACE(sizeof(struct cmsgcred));
 */
struct cmsgcred{
  pid_t cmcred_pid;
  uid_t cmcred_uid;
  uid_t cmcred_euid;  // effective UID
  gid_t cmcred_gid;
  short cmcred_ngroups; // number of groups;
  gid_t cmcred_groups[CMGROUP_MAX];
};


/**
 * @param socklen_t * addrlen  is quite different with socklen addrlen
 * @example if unknown IPv4 or IPv6, use sockaddr_storage
 *  struct sockaddr_storage sa_s;  
 *  socklen_t sa_s_len = sizeof(sa_s); 
 *  memset(&sa_s, 0, sa_s_len);
 *  getsockname(listenfd, (struct sockaddr*)&sa_s, sa_s_len);
 *  printf("%d", sa_s.ss_family);
 * @example if IPv4
 *  struct sockaddr_in sa_in; 
 *  socklen_t sa_in_len = sizeof(sa_in);
 *  memset(&sa_in, 0, sizeof(sa_in);
 *  getsockname(listenfd, (struct sockaddr *)&sa_in, &sa_in_len);
 *  char i4_str[16];
 *  inet_ntop(AF_INET, &sa_in.sin_addr, i4_str, 16);
 *  printf("%d,%s:%d", sa_in.sin_family, i4_str, sa_in.sin_port);
 */
int getsockname(int bindfd, struct sockaddr *localaddr, socklen_t * addrlen)
int getpeername(int bindfd, struct sockaddr *peeraddr, socklen_t * addrlen)


 