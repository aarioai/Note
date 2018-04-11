#include <sys/ioctl.h> 
#include <net/if.h>
#define IFNAMSIZ      16
#define ifc_buf       ifc_ifcu.ifcu_buf;
#define ifc_req       ifc_ifcu.ifcu_req;
#define ifr_addr      ifr_ifru.ifru_addr;
#define ifr_dstaddr   ifr_ifru.ifru_dstaddr;
#define ifr_broadaddr ifr_ifru.ifru_broadaddr;
#define ifr_flags     ifr_ifru.ifru_flags;
#define ifr_metric    ifr_ifru.ifru_metric;
#define ifr_data      ifr_ifru.ifru_data;
struct ifreq{               // interface request
  /**
   * interface request name, e.g. lo, enp0s3
   * @note Under Solaris, the interface name for an alias contains a colon (e.g
   *  "lo" "lo:" "lo:"), while under 4.4BSD, the interface name does not change
   *  for an alias. To handle both cases, we save the last interface name in
   *  lastname and only compare up to a colon
   */
  char ifr_name[IFNAMSIZ];
  union {
    struct  sockaddr ifru_addr;
    struct  sockaddr ifru_dstaddr;
    struct  sockaddr ifru_broadaddr;
    /**
     * @var 
     *  IFF_UP  interface is not up
     *  IFF_BROADCAST
     *  IFF_MULTICAST
     *  IFF_LOOPBACK  loop
     *  IFF_POINTOPOINT p2p SIOCGIFDSTADDR
     */
    short   ifru_flags;
    int     ifru_metric;
    cadrr_t ifru_data;
  } ifr_ifru;
}; 
struct ifconf{
  int ifc_len;      // size of buffer, value-result
  union{
    caddr_t ifcu_buf;       // input from user -> kernel
    struct  ifreq *ifcu_req; // return from kernel -> user
  } ifc_ifcu; 
};

struct arpreq{
  struct  sockaddr arp_pa;
  struct  sockaddr arp_ha;
  int     arp_flags;
};
#define ATF_INUSE 0x01
#define ATF_COM   0x02
#define ATF_PERM  0x04
#define ATF_PUBL  0x08

/**
 * @param int request
 *  [Socket]
 *  [File]
 *  [Interface]
 *    SIOC G/S IF CONF  get/set ifconfig (list of all interfaces), 
 *      result: ifconf{}
 *    SIOC G/S IF FLAGS  get/set interface flags
 *      value:  ifreq{ifr_name}
 *      result: ifreq{ ifr_ifru.ifru_flags }
 *    SIOC G/S IF DSTADDR  get/set point-to-point addr. IFF_POINTOPOINT
 *    SIOC G/S IF BRDADDR  get/set broadcast addr.
 *      IPv4 only
 *    SIOC G/S IF MTU  get/set interface MTU
 *  [ARP]
 *    SIOC G/S/D ARP  get/set/delete ARP entry, return arpreq{}
 *      Systems usually use routing sockets instead of ioctl() to access the ARP
 *        cache.
 *  [Routing]
 *    SIOC ADD/DEL RT  add/delete route
 *  [STREAMS]
 * @return -1 on error with errno;
 *          if with errno EINVAL, the buffer specified is not large enough to
 *            hold the result
 *        >=0
 *          error on the buffer ifconf.ifc_buf is lesser than the result. 
 *            returns 0 without changing &ifconf on some OS(e.g. Berkeley-derived)
 *          success on some OS with change the ifconf.len to the result needs
 *            The real space may not be multiple to sizeof(struct ifreq)
 *            if all the ifreqs are all IPv4 (struct sockaddr), the real space
 *              is equal multiple sizeof(struct ifreq)
 *            if with IPv6 (struct sockaddr_in6), it needs more space for it
 * @note This means the only way we know that our buffer is large enough is to 
 *  issue, save the return length, issue the request again with a larger buffer,
 *  and compare the length with the saved value.
 * @example we don't know how many interfaces the server has
 *  sh$ ifconfig
 *  +--------------------------------------------------------------------------+
 *  |   enp0s3: <UP,BROADCAST,MULTICAST>  mtu 1500
 *  |       inet 192.168.1.12  broadcast 192.168.1.255
 *  |   lo    : <UP,MULTICAST,RUNNING>  mtu 65536
 *  |       inet 127.0.0.1
 *  |   ...
 *  +--------------------------------------------------------------------------+
 *  struct ifconf if_conf;
 *  int len = 2 * sizeof(struct ifreq);   // allocate 2 ifreq{}
 *  char *buf = (char *)malloc(len);
 *  if_conf.ifc_ifcu.ifcu_len = len;
 *  if_conf.ifc_ifcu.ifcu_buf = buf;
 *  if(ioctl(sockfd, SIOCGIFCONF, &if_conf) < 0){
 *    if(errno != EINVAL)
 *      exit(0);   
 *  }
 *  free(buf);
 * @note above only suit for 2 interfaces. If there are 3 or more interface,
 *  ioctl() will return 0 (in some OS) or -1 with errno EINVAL for less room of
 *  the argument &if_conf.
 */
int ioctl(int fd, int request, ...)





/**
 * @note
 *  sh$ netstat -r
 *  +--------------------------------------------------------------------------+
 *  | Destination | Gateway   | Genmask       | F  | MSS | Win | irtt | Iface
 *  +-------------+-----------+---------------+----+-----+-----+------+--------+
 *  | default     | Brdcom.Hm | 0.0.0.0       | UG |  0  |  0  |  0   | enp0s3
 *  | 192.168.1.0 | 0.0.0.0   | 255.255.255.0 | U  |  0  |  0  |  0   | enp0s3
 *  +--------------------------------------------------------------------------+
 * @example
 *  sockfd = socket(AF_ROUTE, SOCK_RAW, 0);
 *  read(sockfd, (struct rt_msghdr *) value, rtm len);
 *  while(){
 *    read(sockfd, (struct rt_msghdr *) result, rtn len);
 *  }
 */
#include <net/route.h>
struct rt_msghdr{     // 
  u_short rtm_msglen;
  u_char  rtm_version;
  /**
   * @var u_char rtm_type
   *  RTM_ADD
   *  RTM_CHANGE
   *  RTM_DELADDR
   *  RTM_DELETE
   *  RTM_DELMADDR
   *  RTM_GET report metrics and other route information, return rt_msghdr
   *  RTM_IFANNOUNCE
   *  RTM_IFINFO
   *  RTM_LOCK
   *  RTM_LOSING
   *  RTM_MISS
   *  RTM_NEWADDR
   *  RTM_NEWMWADDR
   *  RTM_REDIRECT
   *  RTM_RESOLVE
   */
  u_char  rtm_type;
  u_short rtm_index;
  int     rtm_flags;
  /**
   * @var int rtm_addrs
   *  0x01 RTAX_DST     =>  RTA_DST
   *  0x02 RTAX_GATEWAY =>  RTA_GATEWAY
   *  0x04 RTAX_NETMASK =>  RTA_NETMASK
   *  0x08 RTAX_GENMASK =>  RTA_GENMASK
   *  0x10 RTAX_IFP     =>  RTA_IFP
   *  0x20 RTAX_IFA     =>  RTA_IFA
   *  0x40 RTAX_AUTHOR  =>  RTA_AUTHOR
   *  0x80 RTAX_BRD     =>  RTA_BRD
   *       RTAX_MAX
   */
  int     rtm_addrs;
  int     rtm_pid;
  int     rtm_seq;
  int     rtm_errno;
  int     rtm_use;
  u_long  rtm_inits;
  struct rt_metrics rtm_rmx;
};



