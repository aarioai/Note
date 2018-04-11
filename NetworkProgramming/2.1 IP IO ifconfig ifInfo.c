/**
 * shell: ifconfig
 *  enp0s3: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
 *      inet 192.168.1.12  netmask 255.255.255.0  broadcast 192.168.1.255
 *      inet6 fe80::a00:27ff:fe68:5bc6  prefixlen 64  scopeid 0x20<link>
 *      ether 08:00:27:68:5b:c6  txqueuelen 1000  (Ethernet)
 *      RX packets 86185  bytes 40641961 (38.7 MiB)
 *      RX errors 0  dropped 0  overruns 0  frame 0
 *      TX packets 74747  bytes 55261058 (52.7 MiB)
 *      TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
 *
 *  lo: flags=73<UP,LOOPBACK,RUNNING>  mtu 65536
 *      inet 127.0.0.1  netmask 255.0.0.0
 *      inet6 ::1  prefixlen 128  scopeid 0x10<host>
 *      loop  txqueuelen 0  (Local Loopback)
 *      RX packets 14  bytes 3612 (3.5 KiB)
 *      RX errors 0  dropped 0  overruns 0  frame 0
 *      TX packets 14  bytes 3612 (3.5 KiB)
 *      TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
 *
 */
#include <sys/ioctl.h> 
#include <net/if.h>
#define IFI_HW_ADDR_LEN 8      // hardware addrlen
struct ifInfos{       // interfaces
  char  name[IFNAMSIZ];      // INNAMSIZ defined in net/if.h, e.g. enp0s3
  short flags;
  short ifi_flags;
  short mtu;
  struct sockaddr *addr;    // inet & inet6
  struct sockaddr *brdaddr;   //broadcast addr.
  struct sockaddr *dstaddr;   // point-to-point addr.
  u_char  hwAddr[IFI_HW_ADDR_LEN];  // hardware addr., e.g. an Ethernet addr.
  u_short hwlen;      // bytes in hardware address: 0, 6, 8
  short   index;  // index of the interfaces
  struct ifInfos *next;
};
/**
 * Flags
 */
#define IFI_ALIAS 1

void free ifInfos(struct ifInfos *i){
  struct ifInfos *i_next;
  for(i; i != NULL; i = i_next){
    (i->addr != NULL) && free(i->addr);
    (i->brdaddr != NULL) && free(i->brdaddr);
    i_next = i->next;
    free(i);
  }
}

/**
 * 1 Get ifconf.ifreq s  --> enp0s3, lo ....
 * 2 Get SIOCGIFFLAGS from each ifconf.ifreq
 * 3 Get the information in the flags
 * @note
 *  malloc() ifconf.ifc_buf 
 *  ioctl(sockfd, SIOCGIFCONF, &ifreq s);
 *  for(struct ifreq s){     // be careful about the non-constant size of ifreq
 *    check do_alias (Note Solaris' alias end with a colon and BSD's not change)
 *    ioctl(sockfd, SIOCGIFFLAGS, &ifr);
 *    for(flags){
 *      ioctl(sockfd, coverted_flag, &ifre);
 *    }
 *  }
 * @return the first/head struct ifInfos
 *  struct ifInfos *ifi_head, ** ifis;
 *  ifi_head = NULL;
 *  *ifis = &ifi_head;
 *  for(struct ifreq s){
 *    *ifis = ifi;      // the first ifi_head ptr to the first ifi
 *                      // the rest ifis ptr to pre ifi->next
 *    ifis = &(ifi->next);
 *  }
 */
struct ifInfos *getIfInfos(int addr_fam, int show_alias){
  int sockfd, guess_len, last_ifc_len;
  char *buf, *ptr;
  struct ifconf ifc;
  struct ifreq *ifr, ifre;
  /*****************************************************************************
   * Get the ifconf.ifreq s  --> enp0s3, lo ....
   */
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);    // UDP
  guess_len = 50 * sizeof(struct ifreq);    // guess a number 50
  last_ifc_len = 0;
  for(;;){
    buf = malloc(guess_len);
    ifc.ifc_len = guess_len;
    ifc.ifc_buf = buf;
    /**
     * ioctl(sockfd, SIOCGIFCONF, &ifc)
     *  * ifc is a value-result, you need pass a ifc.ifc_len to it as a value.
     *  * if passed ifc.ifc_len is lesser than the real
     *      in some OS, ioctl() returns -1 with errno EINVAL
     *      in some OS, ioctl() returns 0, and ifc.ifc_len will not change
     *  * if success, ifc.ifc_len returns the real number
     */
    if(ioctl(sockfd, SIOCGIFCONF, &ifc) < 0){
      if(errno != EINVAL)
        err_exit("");
    } else{
      if(last_ifc_len == ifc.ifc_len)
        break;      // sucess, buf is not freed
      last_ifc_len = ifc.ifc_len;
    }
    guess_len += 10 * sizeof(struct ifreq);
    free(buf);
  }
  // printf("%d ===> %d", ifc.ifc_len, ifc.ifc_len / sizeof(struct ifreq)); 
  /**
   * if success, ifc.ifc_len returns the real space it holds
   *   The real space may not be multiple to sizeof(struct ifreq)
   *    if all the ifreqs are all IPv4 (struct sockaddr), the real space is equal
   *      multiple sizeof(struct ifreq)
   *    if with IPv6 (struct sockaddr_in6), the real space need more space for it
   */
  size_t sa_sz;
  struct ifInfos *ifi;
  char *chr_ptr, last_name[IFNAMSIZ];
  short ifi_flags;
  for(ptr = buf; ptr < buf + ifc.ifc_len;){
    ifr = (struct ifreq *)ptr;
    ptr += sizeof(ifr->ifr_name);
    #ifdef HAVE_SOCKADDR_SA_LEN
    ptr += max(sizeof(struct ifreq), ifr->ifr_addr.sa_len)
    #else
    switch(ifr->ifr_addr.sa_family){
      #ifdef IPV6
      case AF_INET6:
        ptr += sizeof(struct sockaddr_in6);
        break;
      #endif
      default:      // IPv4, Data-link
        ptr += sizeof(struct sockaddr);
    }
    #endif

    if(addr_fam != ifr->ifr_addr.sa_family)
      continue;
    
    ifi_myflags = 0;
    if(NULL !=(chr_ptr = strchr(ifr->sa_addr, ':')))
      *chr_ptr = 0;
    if(0 == strncmp(last_name,ifr->ifr_name, IFNAMSIZ)){ // alias
      if(!show_alias)
        continue;
      ifi_myflags = IFI_ALIAS;
    }
    memcpy(last_name, ifr->ifr_name, IFNAMSIZ);
    
    ifr2 = *ifr;
    /**
     * SIOCGIFLAG
     * @param-return ifr2{ifr_name}    ==>    ifr2{ifr_ifru.ifru_flags}
     */
    ioctl(sockfd, SIOCGIFFLAGS, &ifr2);
    flags = ifr2.ifr_flags;
    ifi = (struct ifInfos *)calloc(1, sizeof(struct ifInfos));
    memcpy(ifi->name, ifr->name, IFI_NAME);
    
    ifi.flags = flags;
    ifi.ifi_myflags = ifi_myflags;        // or |=
    
    #ifdef HAVE_SOCKADDR_DL_STRUCT
    if(ifr->ifr_addr.sa_family == AF_LINK){
      
    }
    #endif
    
    #if defined(SIOCGIFMTU) && defined(HAVE_STRUCT_ifr2Q_IFR_MTU)
    ioctl(sockfd, SIOCGIFMTU, &ifr2);
    ifi->mtu = ifr2.ifr_mtu;
    #else
    ifi->mtu = 0;
    #endif
    
    /**
     * @todo data link hwaddr 
     */
    
    
    
    /**
     * Get all the flags' informations
     */
    switch(ifr->ifr_addr.sa_family){
      case AF_INET:
        sa_sz = sizeof(struct sockaddr_in);
        ifi->addr = calloc(1, sa_sz);
        memcpy(ifi->addr, (struct sockaddr_in *)&ifr->ifr_addr, sa_sz);
        #ifdef SIOCGIFBRDADDR
        if(flags & IFF_BROADCAST){
          ioctl(sockfd, SIOCGIFBRDADDR, &ifr2);
          ifi->brdaddr = calloc(1, sa_sz);
          memcpy(ifi->brdaddr, (struct sockaddr_in)&ifr2.ifr_broadaddr, sa_sz);
        }
        #endif
        #ifdef SIOCGIFDSTADDR
        if(flags & IFF_POINTOPOINT){
          ifi->dstaddr = calloc(1, sizeof(struct dstaddr));
          ioctl(sockfd, SIOCGIFDSTADDR, &ifr2);
          memcpy(ifi->dstaddr, (struct sockaddr_in *)&ifr2.ifr_dstaddr, sa_sz);
        }
        #endif
        break;
      case AF_INET6:
        sa_sz = sizeof(struct sockaddr_in6);
        ifi->addr = calloc(1, sa_sz);
        memcpy(ifi->addr, (struct sockaddr_in6 *)&ifr->ifr_addr, sa_sz);
        #ifdef SIOGIFDSTADDR
          if(flags & IFF_POINTOPOINT){
            
          }
        #endif
        break;
      default:
        break;
    }
  }
  free(buf);

  
}







 