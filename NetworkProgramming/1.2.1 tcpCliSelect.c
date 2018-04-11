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



ssize_t n, nwritten;
int maxfd_add1;
fd_set rset, wset;
/**
 * @note the conditions are handled with the socket
 *  1. peer TCP sends data, read() returns > 0
 *  2. peer TCP sends FIN, read() returns EOF
 *  3. peer TCP send RST, read() returns -1 with errno
 */
 
/**
 * blocking I/O
 *  select()
 * nonblocking I/O
 *  fcntl() + select()
 */ 
int fl;    // file status flag
fl = fcntl(connfd, F_GETFL, 0);
fcntl(connfd, F_SETFL, fl | O_NONBLOCK);
fl = fcntl(STDIN_FILENO, F_GETFL, 0);
fcntl(STDIN_FILENO, F_SETFL, fl | O_NONBLOCK);
fl = fcntl(STDOUT_FILENO, F_GETFL, 0);
fcntl(STDOUT_FILENO, F_SETFL, fl | O_NONBLOCK);
/**
 * Now it's nonblocking I/O, you need to control buffer by yourself
 *  Max Send Buffer and Max Receive Buffer
 *  stdin2sendbuf --> sendbuf+x = &sendbuf[x]
 *       stdin2sendbuf --> sendbuf+x+x2
 *            stdin2sendbuf --> sendbuf+x+x2+.. <= sendbuf+SERV_BUF_SIZE     
 *        +-----------------------------------------------------+
 *        | &sendbuf | ...SEND BUF... | &sendbuf[SERV_BUF_SIZE] |
 *        +-----------------------------------------------------+
 *           --> sendbuf2send = buf+y = &buf[y]
 *                    --> sendbuf2send 
 *                    --> sendbuf2send
 *  ptr recv2recvbuf
 *  ptr recvbuf2stdout
 * @note in order to prevent stdin2sendbuf crossing &sendbuf[SERV_BUF_SIZE],
 *  read(STDIN_FILENO, stdin2sendbuf, *(sendbuf+SERV_BUF_SIZE) - stdin2sendbuf)
 */
//char sendbuf[SERV_BUF_SIZE], char recvbuf[SERV_BUF_SIZE]; 
char buf[SERV_BUF_SIZE]; 
int send_sz = SERV_BUF_SIZE / sizeof(struct args);
struct args args_arr[send_sz]; 
int recv_sz = SERV_BUF_SIZE / sizeof(struct results);
struct results results_arr[recv_sz];
struct args *stdin2sendbuf, *sendbuf2send, *recv2outbuf, *outbuf2stdout;
stdin2sendbuf = sendbuf2send = args_arr;
recv2recvbuf = recvbuf2stdout = results_arr;
int stdin_eof_to_fin = 0;
 
maxfd_add1 = max(max(STDIN_FILENO, STDOUT_FILENO), connfd) + 1; 
for(;;){
  FD_ZERO(&rset);
  FD_ZERO(&wset);
  if(!stdin_eof_to_fin && stdin2sendbuf < (sendbuf + send_sz))
    FD_SET(STDIN_FILENO, &rset);
  if(recv2recvbuf < &results_arr[recv_sz])
    FD_SET(connfd, &rset);
  if(sendbuf2send < stdin2sendbuf)
    FD_SET(connfd, &wset);
  if(recvbuf2stdout < recv2recvbuf)
    FD_SET(STDOUT_FILENO, &wset);

  vDebug("select()",
    select(maxfd_add1, &rset, &wset, NULL, NULL)
  );

  if(FD_ISSET(STDIN_FILENO, &rset)){
    if((n = read(STDIN_FILENO, buf, SERV_BUF_SIZE)) < 0){
      if(errno != EWOULDBLOCK)
        err(errno, LOG_ERR, "stdin out");
    } else (n == 0){        // Ctrl + D
      fprintf(stderr, "stdin ==> EOF, wait for sendbuf2send, send a FIN\n");
      stdin_eof_to_fin = 1;
      if(sendbuf2send == stdin2sendbuf)
        vDebug("shutdown()",
          shutdown(connfd, SHUT_WR)         // send a FIN
        );
    } else {
      if(2 != sscanf(buf, "%ld %ld", &args.arg1, &args.arg2))
        err(0, LOG_ERR, "stdin type error");
      *(stdin2sendbuf++) = args;
      FD_SET(connfd, &wset);
    }
  } 
  
  if(FD_ISSET(connfd, &wset) && ((n = stdin2sendbuf - sendbuf2send) > 0)){    
    if((nwritten = write(connfd, sendbuf2send, n * sizeof(struct args))) < 0){
      if(errno != EWOULDBLOCK)
        err(errno, LOG_ERR, "write()");
    } else {
      sendbuf2send += nwritten / sizeof(struct args);
      if(sendbuf2send == stdin2sendbuf){
        stdin2sendbuf = sendbu2send = results_arr;
        /**
         * In order the first shutdown() not success when sendbuf2send != stdin2sendbuf
         */
        if(stdin_eof_to_fin)
          vDebug("shutdown()",
            shutdown(connfd, SHUT_WR)
          );
      }
    }
  }
  
  if(FD_ISSET(connfd, &rset)){
    if((n = read(connfd, recv2recvbuf, sizeof(struct results))) < 0){
      if(errno != EWOULDBLOCK)
        err(errno, LOG_ERR, "");
    } else if(n==0){
      // it's necessary, otherwise when send a FIN, client'll be blocked by this
      if(stdin_eof_to_fin)
        return;   
      else
        err(errno, LOG_NOTICE, "Server terminated prematurely");
    } else{
      ++recv2recvbuf;
      FD_SET(STDOUT_FILENO, &wset);
    }
  }
  
  if(FD_ISSET(STDOUT_FILENO, &wset) && ((n = recv2recvbuf - recvbuf2stdout) > 0)){
    while(recv2recvbuf - recvbuf2stdout > 0){
      if(fprintf(stdout, "= %d\n", (*recvbuf2stdout).sum) < 0){
        if(errno != EWOULDBLOCK)
          err(errno, LOG_ERR, "");
      } else {
        ++recvbuf2stdout;
        if(recvbuf2stdout == recv2recvbuf)
          recv2recvbuf = recvbuf2stdout = results_arr;
      }
    }
  }
  
}