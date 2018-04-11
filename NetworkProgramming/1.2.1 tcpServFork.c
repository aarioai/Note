// sudo ./socketServ.out &   otherwise permission rejected


int listenfd;
vDebug("socket()", 
 listenfd = socket(AF_INET, SOCK_STREAM, 0)
);


struct sockaddr_in i4; // IPv4
//bzero(&i4, sizeof(i4)); 
memset(&i4, 0, sizeof(i4)); // set to 0 using bzero()
i4.sin_family = AF_INET;
i4.sin_port = htons(SERV_LISTEN_PORT);  // consult Little Endian and Big Endian
i4.sin_addr.s_addr = htonl(INADDR_ANY);
// i4.sin_addr.s_addr = inet_addr("127.0.0.1");
//inet_pton(AF_INET, "127.0.0.1", &i4.sin_addr); 
vDebug("bind()",
    bind(listenfd, (const struct sockaddr*)&i4, sizeof(i4))
);


/**
 * struct sockaddr_in sa_s;        // if IPv4
 * struct sockaddr_in6 sa_s;       // if IPv6
 * struct sockaddr_storage sa_s;   // if unknown
 */
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
//struct sockaddr cli_addr;
//socklen_t cli_addr_len;
int connfd;
char recvbuf[SERV_BUF_SIZE + 1], buf[SERV_BUF_SIZE + 1];
struct args args;
struct results results;
for(;;){
 /**
  * back to for(;;) on errno==EINTR to restart it
  */
 if(0 ==
  vDebug("accept()",
   // connfd = accept(listenfd, (struct sockaddr *)&cli_addr, &cli_addr_len)
   connfd = accept(listenfd, (struct sockaddr *)NULL, NULL)
  ) 
 ) continue;
 /**
  * Concurrent[kənˈkɜ:rənt] Servers
  * fork() duplicates a child process with listenfd and connfd of its own.
  */
 if( (pid = fork()) == 0){
  vDebug("close(listenfd)",
   close(listenfd)    // child closes listening socket
  );
  /*
  if( read(connfd, recvbuf, SERV_BUF_SIZE) == 0)
   snprintf(buf, SERV_BUF_SIZE, "Client: %s", recvbuf);
  else
   snprintf(buf, SERV_BUF_SIZE, "Recv Nothing From Client!");
  vDebug("write()",
   write(connfd, buf, strlen(buf))
  );
  */
  
  if( (n=read(connfd, &args, sizeof(args))) <= 0){
   printf("Recv Nothing From Client!\n");
  } else {
   results.sum = args.arg1 + args.arg2;
   printf("Cli(): %ld + %ld = ", args.arg1, args.arg2);
   printf("%ld\n", results.sum);
   vDebug("write()",
    write(connfd, &results, sizeof(results))
   );
  }
  /**
   * Optional: child closes connected socket
   * it's not required since the next statement calls exit(), and part of 
   *  process termination is to close all open descriptors by the kernel.
   */
  vDebug("close(connfd-child)",
   close(connfd)
  );
  exit(0);                // child terminates
 } else if(pid >0){
  /**
   * Delivered signal SIGCHLD blocks parent to call accept(), the kernel 
   *  causes the accept() to return an error of EINTR(interrupted system
   *  call). Then sigChld() executes, wait() fetches the child's PID.
   */
  signal(SIGCHLD, sigChld);
 }
 vDebug("close(connfd)",
  close(connfd)           // parent closes connected socket
 );

}



struct sockaddr_in6 i6;
i6.sin6_family = AF_INET6;
i6.sin6_posrt = htons(4950);
inet_pton(AF_INET6, "2001:db8:8714:3a90::12", &i6.sin6_addr);
bind(listenfd, (struct sockaddr*)&i6, sizeof(i6));