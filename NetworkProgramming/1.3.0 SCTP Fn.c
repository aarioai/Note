/**
 * @see http://osxr.org/linux/source/include/uapi/linux/sctp.h
 * sudo yum install lksctp*
 * gcc -Wall -g sock.h sctpServ.c -lsctp -o sctpServ.out
 */
#include <netinet/sctp.h>
typedef int32_t __s32; // http://osxr.org/linux/source/tools/virtio/linux/types.h#0022
typedef __s32 sctp_assoc_t;// http://osxr.org/linux/source/include/uapi/linux/sctp.h#0060

/**
 * Add or remove bind a set of addresses on a socket
 * @param int flags
 *  SCTP_BINDX_ADD_ADDR
 *  SCTP_BINDX_REM_ADDR
 */
int sctp_bindx(int sockfd, const struct sockaddr *addrs, int addr_count, int flags)

int sctp_connectx(int sockfd, const struct sockaddr *addrs, int addr_count)

/**
 * get the list of the peer addresses
 */
int sctp_getpaddrs(int sockfd, sctp_assoc_t id, struct sockaddr **addrs)
void sctp_freeaddrs(struct sockaddr *addrs)

int sctp_getladdrs(int sockfd, sctp_assoc_t id, struct sockaddr **addrs)
void sctp_freeladdrs(struct sockaddr *addrs)

/**
 * @param int flags
 *  SCTP_UNORDERED un-ordered
 *  SCTP_ADDR_OVER in the one-to-many
 *  SCTP_ABORT
 *  SCTP_EOF
 * @param uint32_t timetolive in milliseconds
 */
ssize_t  sctp_sendmsg(int sockfd, const void *msg, size_t msglen, 
                 struct sockaddr *to, socklen_t tolen,
                 uint32_t ppid,
                 uint32_t flags, uint16_t stream_no,
                 uint32_t timetolive, uint32_t context)

ssize_t  sctp_recvmsg(int sockfd, void *msg, size_t msglen,
                 struct sockaddr *from, socklen_t *fromlen,
                 struct sctp_sndrcvinfo *sinfo, int *msg_flags)
                 
int sctp_opt_info(int sockfd, sctp_assoc_t id, int opt, void *arg, socklen_t *sz)

int sctp_peeloff(int sockfd, sctp_assoc_t id)