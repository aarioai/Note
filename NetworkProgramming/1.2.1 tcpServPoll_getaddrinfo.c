char *host = NULL,
     *service = "9877";
     
int n;
struct addrinfo hints, *ai, *ai4free;
memset(&hints, 0, sizeof(struct addrinfo));
hints.ai_flags = AI_CANONNAME;
hints.ai_family = AF_UNSPEC;
hints.ai_socktype = SOCK_STREAM;
if(0 != (n = getaddrinfo(host, service, &hints, &ai))){
  printf("getaddrinfo() error:%d(%s)", n, gai_strerror(n));
  exit(0);
}
ai4free = ai;
if(ai == NULL){
  printf("getaddrinfo() error");
  exit(0);
}
int listenfd;
const int on = 1;
while(ai != NULL){
  if((listenfd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol)) < 0)
    continue; // try next ai
  vDebug("setsockopt()",
    setscokopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))
  );
  if(0 == bind(listenfd, ai->ai_addr, ai->ai_addrlen))
    break;  // success
  vDebug("close()",
    close(listenfd)
  );
  ai = ai->ai_next;
}
freeaddrinfo(ai4free);

vDebug("listen()",
  listen(listenfd, SERV_LISTEN_QUEUES)
);


pid_t pid;
struct sockaddr cli_addr;
socklen_t cli_addr_len;
int connfd;
char recvbuf[SERV_BUF_SIZE + 1], buf[SERV_BUF_SIZE + 1];
struct args args;
struct results results;
memset(&results, 0, sizeof(results));
/**
 * Concurrent[kənˈkɜ:rənt] Servers for multiple clients
 * @note OPEN_MAX is intentionally not defined because it is no longer
 *  constant in Linux, it is runtime changeable.
 *  Use sysconf(_SC_OPEN_MAX) to query the same information.
 */
struct pollfd clis[sysconf(_SC_OPEN_MAX)];
int i, nready, connfd, tempfd;
nfds_t maxi;
clis[0].fd = listenfd;
clis[0].events = POLLRDNORM;
#define CLI_AVL -1
for(i=1; i < sysconf(_SC_OPEN_MAX); ++i)
 clis[i].fd = CLI_AVL;
maxi=0;
for(;;){
  /**
   * @todo INFTIM is undefined
   */
  vDebug("poll()",
    nready = poll(clis, maxi+1, INFTIM)
  );
  /**
   * new client connection
   * the avaliable of a new connection on a listening sokcet can be considered
   *  either normal(POLLRDNORM) or priority(POLLRDBAND) data.
   */
  if(clis[0].revents & POLLIN){
    cli_addr_len = sizeof(cli_addr_len);
    vDebug("accept()",
    connfd=accept(listenfd, (struct sockaddr*)&cli_adrr, &cli_addr_len)
  );
  for(i=1;i<sysconf(_SC_OPEN_MAX);++i){
    if(clis[i].fd < 0){
      clis[i].fd = connfd;
      clis[i].events = POLLRDNORM;
      break;
    }
  }
  if(i>maxi) maxi = i;
  if(--nready <=0)
    continue;
  }
}
for(i=1;i<=maxi;++i){
  if((tempfd = clis[i].fd)<0)
    continue;
  if(clis[i].revents & (POLLRDNORM | POLLERR)){
    if(read(tempfd, &args, sizeof(args)) <=0){
      vDebug("close(tempfd)",
        close(tempfd)
      );
      clis[i].fd = CLI_AVL;
    } else{
      results.sum = args.arg1 + args.arg2;
      printf("Cli(%d): %ld + %ld = ", tempfd, args.arg1, args.arg2);
      printf("%ld\n", results.sum);
      vDebug("write()",
        write(tempfd, &results, sizeof(results))
      );
    }
    if(-nready <=0) break;
  }
}