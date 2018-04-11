int listenfd;

vDebug("socket()",
  listenfd = socket(AF_INET, SOCK_STREAM, 0)
);


/**
 * IPv4
 */
struct sockaddr_in i4; // IPv4
//bzero(&i4, sizeof(i4)); 
memset(&i4, 0, sizeof(i4)); // set to 0 using bzero()
i4.sin_family = AF_INET;
i4.sin_port = htons(SERV_LISTEN_PORT);  // consult Little Endian and Big Endian
inet_pton(AF_INET, "127.0.0.1", &i4.sin_addr); 
vDebug("connect()",
  connect(listenfd, (struct sockaddr *)&i4, sizeof(i4))
);


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
