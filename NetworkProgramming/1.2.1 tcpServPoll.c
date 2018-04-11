int listenfd;
vDebug("socket()", 
  listenfd = socket(AF_INET, SOCK_STREAM, 0)
);


struct sockaddr_in i4; // IPv4
//bzero(&i4, sizeof(i4)); 
memset(&i4, 0, sizeof(i4)); // set to 0 using bzero()
i4.sin_family = AF_INET;
i4.sin_port = htons(SERV_LISTEN_PORT);  // consult Little Endian and Big Endian
// i4.sin_addr.s_addr = htonl(INADDR_ANY);
// i4.sin_addr.s_addr = inet_addr("127.0.0.1");
inet_pton(AF_INET, "127.0.0.1", &i4.sin_addr); 
vDebug("bind()",
  bind(listenfd, (const struct sockaddr*)&i4, sizeof(i4))
);


struct sockaddr_storage sa_s;
socklen_t sa_s_len = sizeof(sa_s);
memset(&sa_s, 0, sa_s_len);
vDebug("getsockname(sa_s)",
  getsockname(listenfd, (struct sockaddr *) &sa_s, &sa_s_len)
);
printf("ss_family: %d  ", sa_s.ss_family);

struct sockaddr_in sa_in;
socklen_t sa_in_len = sizeof(sa_in);
memset(&sa_in, 0, sizeof(sa_in));
vDebug("getsockname(sa_in)",
  getsockname(listenfd, (struct sockaddr *)&sa_in, &sa_in_len)
);
//printf("family: %d  ", sa_in.sin_family);
printf("sin_port: %d  ", sa_in.sin_port);
if(!sa_in.sin_port > 0){
  printf("port error");
  exit(0);
}

char i4_str[INET_ADDR_STRLEN];
inet_ntop(AF_INET, &sa_in.sin_addr, i4_str, INET_ADDR_STRLEN);
printf("inet_ntop(sin_addr): %s\n", i4_str);


vDebug("listen()",
  listen(listenfd, SERV_LISTEN_QUEUES)
);

ssize_t n;
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
    if((n=read(tempfd, &args, sizeof(args))) <=0){
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