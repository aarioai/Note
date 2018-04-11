#include <netdb.h>

struct addrinfo{
  /**
   * @var 
   *  AI_PASSIVE
   *  AI_CANONNAME needs return the canonical name
   *  AI_NUMERICHOST only accept a dotted-decimal(IPv4) or hext string for
   *    arg const char *host
   *  AI_NUMERICSERV only accept a decimal port for arg const char *service;
   *  AI_V4MAPPED
   *  AI_ALL
   *  AI_ADDRCONFIG
   */
  int ai_flags; // can specify more than one times
  /**
   * @var
   *  AF_UNSPEC
   *  AF_INET6
   *  AF_INET
   */
  int ai_family;
  int ai_socktype;        // SOCK_STREAM  SOCK_DGRAM  SOCK_SEQPACKET
  int ai_protocol;        // 0 or IPPROTO_TCP  IPPROTO_UDP  IPPROTO_SCTP
  socklen_t ai_addrlen;
  char *ai_canonname;
  struct sockaddr *ai_addr; // sockaddr_in{}  sockaddr_in6{}  sockaddr_un{} ...
  struct addrinfo *ai_next;
};
/**
 * Despite the fact that getaddrinfo() is harder than gethostbyname() and 
 *  getservbyname(), it's still more useful.
 * @param const char *host is either a host name or an dotted-decimal string 
 *  for IPv4 or a hex string for IPv6
 * @param const char *service is either a service name or a decimal port number
 * @param const struct addrinfo hints can be a null ptr
 * @param/return struct addrinfo **result all the storage are obtained dynamically.
 *  e.g., from malloc(). We need freeaddrinfo() to release it.
 * @return int 0 on success
 * @example
 *  struct addrinfo *host_serv(const char *host, const char *service,
 *                              int family, int socktype){
 *    struct addrinfo *ai_hints_, **ai_results_;
 *    memset(ai_hints_, 0, sizeof(struct addrinfo));
 *    ai_hints_->ai_flags = AI_CANONNAME;
 *    ai_hints_->ai_family = family;
 *    ai_hints_->ai_socktype = socktype;
 *    int n;
 *    if(0 != (n = getaddrinfo(host, service, &hints, &ai))){
 *      printf("gai_strerror(%d): %s", n, gai_strerror(n));
 *      return NULL;
 *    }
 *    return ai_results_;
 *  }
 * @example 
 *  int tcp_connect(const char *host, const char *service){
 *    struct addrinfo hints, *ai4free, *ai;
 *    memset(&hints, 0, sizeof(struct addrinfo));
 *    hints.ai_family = AF_UNSPEC;
 *    hints.ai_socktype = SOCK_STREAM;
 *    int n;
 *    if(0 != (n = getaddrinfo(host, service, &hints, &ai))){
 *      printf("gai_strerror(%d): %s", n, gai_strerror(n));
 *      exit(0);
 *    }
 *    ai4free = ai;
 *    int connfd;
 *    while(NULL != (ai = ai->ai_next)){
 *      if((connfd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol))
 *         < 0 )
 *        continue;
 *      if(0 == connect(connfd, ai->ai_addr, ai->ai_addrlen))
 *        break;  // success
 *    }
 *    if(ai == NULL)
 *      exit(0);
 *    freeaddrinfo(ai4free);
 *    return connfd;
 *  }
 */
int getaddrinfo(const char *host, const char *service,
                const struct addrinfo *hints, struct addrinfo **results)
           
/**
 * @int getaddrinfo_rtn return value of getaddrinfo()
 */ 
const char *gai_strerror(int getaddrinfo_rtn)
void freeaddrinfo(struct addrinfo *ai)

/**
 * @param int flags
 */
int getnameinfo(const struct sockaddr *sockaddr, socklen_t addrlen,
                char *host, socklen_t hostlen,
                char *serv, socklen_t servlen, int flags);
                          
                          
                          
                          
                          
                          
                          
struct hostent{   // host entry, IPv4 only, obsoleted
  char *h_name;       // canonical[kə'nɒnɪkl] name of host \0
  char **h_aliases;   // 
  int h_addrtype;     // e.g. AF_INET
  int h_length;       // e.g. sizeof(sockaddr_in)
  char **h_addr_list; // 
  
};
/**
 * IPv4 only, obsoleted, use getaddrinfo() instead
 */
struct hostent *gethostbyname(const char *hostnm)
struct hostent *gethostbyaddr(const char *addr, socklen_t len, int family)


struct servent{     // IPv4 only, obsoleted
  char *s_name;
  char **s_aliases;
  int s_port;
  char *s_proto;
};
/**
 * IPv4 Only, obsoleted
 * @note sh$ cat /etc/services
 */
struct servent *getservbyname(const char *serv_nm, const char *proto_nm)
/**
 * @param int port htons(port)
 */
struct servent *getservbyport(int port, const char *proto_nm)