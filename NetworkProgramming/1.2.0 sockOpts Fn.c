/**
 * @param int lvl{opt}
 *  SOL_SOCKET
 *    SO_BROADCAST
 *    SO_DEBUG TCP only
 *    SO_DONTROUTE tell the kernel that the destination is on a locally attached
 *      network and not to perform a lookup of the routing table
 *    SO_ERROR
 *    SO_KEEPALIVE if no data exchanged for 2 hours, TCP automatically sends a
 *      "keep-alive probe"(a TCP segment) to the peer, the peer must respond
 *      1 If the peer responds with an ACK, but is not notified. Resend probe
 *      2 If the peer responds with an RST, socket is closed with ECONNNRESET
 *      3 If no response, TCP sends 8 more probes, 75 seconds apart. TCP'll
 *          give up if no response within 11 minutes and 15 seconds, the socket
 *          is closed with ETIMEDOUT
 *    SO_LINGER see struct linger{} below
 *      1 If l_onoff=0, SO_LINGER turns off. close() returns immediately
 *      2 If l_linger=0, TCP discards any data still remaining in the socket
 *          send buffer and sends an RST to the peer, not the normal 4-packet.
 *      3 If l_onoff is on, l_linger>0, kernel lingers when socket is closed.
 *          If there's any data still remaining in the socket send buffer, the
 *          process is put to sleep until either:
 *            (1) all the data is sent and acknowledged by the peer TCP;
 *            (2) the linger time expires, close() returns EWOULDBLOCK
 *       +---------------------------------|-----------------------------------+
 *       |  Default Operation of close(): returns immediately
 *       +---------------------------------|-----------------------------------+
 *       | write()                      -->          (SRB:socket receive buffer)
 *       |                                       busy server, data queued in SRB 
 *       | close()               --FIN M-->   
 *       | close() returns immediately    
 *       |                                            read queued data, then FIN
 *       |                                  <--ACK of data & FIN M--
 *       |                                  <--FIN N--                   close()
 *       |                     --ACK N+1-->
 *       +---------------------------------|-----------------------------------+
 *         The client's close() can return before the server reads the remaining
 *          data in its socket receive buffer. The server may crash before 
 *          'read queued data, then FIN', and the client will never know.
 *       +---------------------------------|-----------------------------------+
 *       |  close() with SO_LINGER, l_onoff!=0; l_linger>0
 *       +---------------------------------|-----------------------------------+
 *       |     write()                  -->          (SRB:socket receive buffer)
 *       |                                       busy server, data queued in SRB 
 *       |     close()           --FIN M-->
 *       |---------------------------------+
 *       |      close() returns in         |          read queued data, then FIN
 *       |       l_linger seconds          |<--ACK of data & FIN M--
 *       |---------------------------------+
 *       |                                  <--FIN N--                   close()
 *       |                     --ACK N+1-->
 *       +---------------------------------|-----------------------------------+
 *         If time l_linger is smaller than 'ACK M+1' despondence, It'll be same
 *          as above. And close() returns -1 with errno EWOULDBLOCK. Only if 
 *          'ACK M+1' responds in the period l_linger seconds, the client'll know
 *          that the server has read its data.
 *       +---------------------------------|-----------------------------------+
 *       |  shutdown(listenfd, SHUT_WR) : peer has received data
 *       +---------------------------------|-----------------------------------+
 *       | write()                      -->          (SRB:socket receive buffer)
 *       |                                       busy server, data queued in SRB 
 *       | shutdown()            --FIN M-->
 *       |                                  <--ACK of data & FIN M--
 *       |                                            read queued data, then FIN
 *       |                                  <--FIN N--                   close()
 *       | read() returns 0
 *       |                     --ACK N+1-->
 *       +---------------------------------|-----------------------------------+
 *    SO_OOBINLINE
 *    SO_RCVBUF advertised window; TCP [8192,61440]; UDP[,9000,]
 *       It must be set before connect()/listen() coz of TCP Window Scale
 *       It should be more than 4 times the MSS.
 *       +---------------------------------------------------------------------+
 *       | Client |      MSS=1460; both socket buffers=6*1460=8760       | Serv
 *       +---------------------------------------------------------------------+
 *       |    --SYN6 1460bytes-->  --SYN5 1200bytes-->  --SYN4 800bytes--> 
 *       |              <--ACK1--            <--ACK2--           <--ACK3-- 
 *       +---------------------------------------------------------------------+
 *       Pipe: a TCP connection between two endpoints
 *       Even though the both socket buffers is 6 times MSS, and it can only 
 *        send 3 segments of data in the pipe. coz the client TCP must keep a 
 *        copy of each segment until the ACK is received.
 *       BandWidth-Delay Product: The capability of a pipe.
 *        BWDP = bandwidth bit/sec * RTT sec * 8 bit/byte
 *    SO_RCVLOWAT
 *    SO_RCVTIMEO timeval{} receive timeout
 *    SO_SNDTIMEO timeval{} send timeout
 *    SO_SNDBUF
 *    SO_SNDLOWAT
 *    SO_REUSEADDR allow local address reuse, a port to bind multiple address
 *      e.g. 192.168.0.10:80 127.0.0.1:80 ...
 *    SO_REUSEPORT allow local port reuse
 *    SO_TYPE get socket type
 *    SO_USELOOPBACK default ON, make socket receives a copy of everything
 *       sent on the socket. It applies only to sockets in the AF_ROUTE.
 *  IPPROTO_IP
 *  IPPROTO_ICMPV6
 *  IPPROTO_IPV6
 *  IPPROTO_IP
 *  IPPROTO_TCP
 *    TCP_MAXSEG
 *    TCP_NODELAY disables TCP's Nagle algorithm; default enabled; Nagle algo
 *      -rithm is to reduce packets smaller than the MSS on a WAN.
 *      E.g. we send "Hi@Aaron" 250ms for each char, and the RTT is 600ms. 
 *       +---------------------------------------------------------------------+
 *       | TCP_NODELY=1, disables Nagle, send data regularly
 *       |                        0--H-->
 *       |                      250--i-->
 *       |                      500--@-->
 *       |       <--ACK for H-- 600
 *       |                      750--L-->
 *       |       <--ACK for i-- 850
 *       |                     1000--e-->
 *       |       <--ACK for @--1100
 *       |                     1250--f-->
 *       |       <--ACK for L--1350 
 *       |       <--ACK for e--1600 
 *       |       <--ACK for f--1850
 *       +---------------------------------------------------------------------+
 *       
 *       +---------------------------------------------------------------------+
 *       | TCP_NODELY=0, enable Nagle, blocking send data<MSS until ACK back
 *       +---------------------------------------------------------------------+
 *       |                      0--H-->
 *       | 250--i--> 500-->@-->#(without piggybacked ACK, store in buffer)
 *       |   <--ACK for H--  600--i@-->(piggyback ACK, send buffer)
 *       | 750--L--> 1000--e-->#       
 *       |   <--ACK for i@--1200--Le-->
 *       | 1250--f-->#                 
 *       |   <--ACK for Le--1800 --f-->
 *       |   <--ACK for f--2400        
 *       +---------------------------------------------------------------------+
 *       There's a problem here, assume a client sends smaller data (A + B),
 *       the server needs to receive both A and B then response. It'll be block
 *       -ing when receive one of them.
 *       +---------------------------------------------------------------------+
 *       | write()              0--A--> |
 *       | write() 250--B-->#  blocking |
 *       |                              |         A recved, blocking for B          
 *       +---------------------------------------------------------------------+ 
 *       You can fix it:
 *        1. Use writev() instead of two calls to write()
 *        2. Copy data A and B into a single buffer with write() once
 *  IPPROTO_SCTP
 *    SCTP_EVENTS with (const struct sctp_event_subscribe *) opt_val
 *      @see http://osxr.org/linux/source/include/uapi/linux/sctp.h#393
 *      struct sctp_event_subscribe{
 *        __u8 sctp_data_io_event; // allow to see the sctp_sndrcvinfo{}
 *        __u8 sctp_association_event;
 *        __u8 sctp_address_event;
 *        __u8 sctp_send_failure_event;
 *        __u8 sctp_peer_error_event;
 *        __u8 sctp_shutdown_event;
 *        __u8 sctp_partial_delivery_event;
 *        __u8 sctp_adaptation_layer_event;
 *        __u8 sctp_authentication_event;
 *        __u8 sctp_sender_dry_event;
 *      };
 *      struct sctp_sndrcvinfo {
 *        __u16 sinfo_stream;       // stream number
 *        __u16 sinfo_ssn;
 *        __u16 sinfo_flags;
 *        __u32 sinfo_ppid;         // peer id
 *        __u32 sinfo_context;
 *        __u32 sinfo_timetolive;
 *        __u32 sinfo_tsn;
 *        __u32 sinfo_cumtsn;
 *        sctp_assoc_t sinfo_assoc_id;
 *      };
 * @param int opt_nm
 * @param void *opt_val
 * @return int 0 on success; -1 on error with errno
 * @example
 *  socklen_t len;
 *  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
 *  getsockopt(sockfd, IPPROTO_TCP, &opt_val, &len);
 */
struct linger{
  int l_onoff;    // 0=off, nonzero=on
  int l_linger;   // linger time, POSIX specifies units as seconds
};
union opt_val{
  int i_val; 
  long l_val; 
  struct linger linger_val; 
  struct timeval timeval_val
} opt_val;
int getsockopt(int sockfd, int lvl, int opt_nm, void *opt, socklen_t *optlen)
int setsockopt(int sockfd, int lvl, int opt_nm, const void *opt, socklen_t optlen)