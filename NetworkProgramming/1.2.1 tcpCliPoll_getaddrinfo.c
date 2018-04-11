char *host = "127.0.0.1",
     *service = "9877";

int n;
struct addrinfo hints, *ai, *ai4free;
if(0 != (n = getaddrinfo(host, service, &hints, &ai))){
  printf("getaddrinfo() error: %d(%s)", n, gai_strerror(n));
  exit(0);
}
ai4free = ai;
int connfd;
const int on = 1;
if(ai == NULL){
  printf("getaddrinfo() error");
  exit(0);
}
while(ai != NULL){
  if((connfd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol)) < 0)
    continue; // try next

  if( 0== connect(connfd, ai->ai_addr, ai->ai_addrlen))
    break; // success
  vDebug("close()",
    close(connfd);  // connect() error, close() socket()
  );
  ai = ai->ai_next;
}
freeaddrinfo(ai4free);

struct sockaddr_storage ss;
socklen_t len = sizeof(struct sockaddr_storage);
vDebug("getpeername()",
  getpeername(connfd, (struct sockaddr *)&ss, &len)
);
switch(ss.sa_family){
  case AF_INET:{
    struct sockaddr_in i4 = (struct sockaddr_in)ss;
    char i4_str[INET_ADDR_STRLEN);
    if(NULL != inet_ntop(i4.sin_family, &i4, &i4_str, INET_ADDR_STRLEN))
      printf("ip:%s\n", i4_str);
    } break;
  default:
    printf("unknown ss.sa_family:%d in switch(){}", ss.sa_family);
    exit(0);
}








char sendbuf[SERV_BUF_SIZE];
struct args args;
struct results results;

nfds_t maxfd = 2;
struct pollfd fds[maxfd];
fds[0].fd = connfd;
fds[0].events = POLLIN;
fds[1].fd = fileno(stdin);
fds[1].events = POLLIN;

/**
 * @note the conditions are handled with the socket
 *  1. peer TCP sends data, read() returns > 0
 *  2. peer TCP sends FIN, read() returns EOF
 *  3. peer TCP send RST, read() returns -1 with errno
 */
for(;;){
  vDebug("poll()",
    poll(fds, maxfd + 1, INFTIME)
  );
  if(fds[0].revents & POLLRDNORM){
    if((n= read(connfd, &results, sizeof(results))) > 0)
      printf("Serv: %ld; n=read()=%d", results.sum, n);
  }
  if(fds[1].revents & (POLLRDNORM | POLLERR)){
    if( NULL != fgets(sendbuf, SERV_BUF_SIZE, stdin) ){
      if(2 != sscanf(sendbuf, "%ld %ld", &args.arg1, &args.arg2)){
        vDebug("shutdown()",
          shutdown(connfd, SHUT_WR)     // send FIN
        );
        printf("invalid input:%s", sendbuf);
        continue;
      }
     
       /**
        * First write() to elicit[ɪˈlɪsɪt] the RST
        */
      vDebug("write()",
        //write(connfd, sendbuf, strlen(sendbuf))
        write(connfd, &args, sizeof(args))
      );
      args.arg1 += args.arg2;
      args.arg2 *= args.arg1;
       //sleep(1);
       /**
        * Second write() to generate a SIGPIPE in server. The default action of 
        *  SIGPIPE is to terminate the process.
        */
      vDebug("write()",
        write(connfd, &args, sizeof(args))
      );
    }
  }
}