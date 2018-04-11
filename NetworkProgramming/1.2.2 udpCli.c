int sockfd;

vDebug("socket()",
  sockfd = socket(AF_INET, SOCK_DGRAM, 0)
);
struct sockaddr_in i4;
socklen_t i4len = sizeof(i4);
memset(&i4, 0,i4len);
i4.sin_family = AF_INET;
i4.sin_port = htons(SERV_LISTEN_PORT);
inet_pton(AF_INET, "127.0.0.1", &i4.sin_addr);

ssize_t n;
char buf[SERV_BUF_SIZE];
struct args args;
struct results results;

nfds_t maxi = 2;
struct pollfd fds[maxi];
fds[0].fd = sockfd;
fds[0].events = POLLRDNORM;
fds[1].fd = fileno(stdin);
fds[1].events = POLLRDNORM;
for(;;){
  vDebug("poll()",
    poll(fds, maxi+1, INFTIM)
  );
  if(fds[1].revents & (POLLRDNORM)){
    if(NULL != fgets(buf, SERV_BUF_SIZE, stdin)){
      vDebug("sscanf()",
        sscanf(buf, sizeof(buf), "%ld %ld", &args.arg1, &args.arg2)
      );
      vDebug("sento()",
        sendto(sockfd, &args, sizeof(args), 0, (const struct sockaddr*)&i4, i4len)
      );
      
      args.arg1 += args.arg2;
      args.arg2 *= args.arg1;
      vDebug("sento()",
        sendto(sockfd, &args, sizeof(args), 0, (const struct sockaddr*)&i4, i4len)
      );
    }
  }
  if(fds[0].revents & (POLLRDNORM | POLLERR)){
      vDebug("recvfrom()",
        n = recvfrom(sockfd, &results, sizeof(results), 0, NULL, NULL)
      );
      /**
       * UDP string'll not end with an EOF, so you need to add it
       * rtn_str[n] = EOF;  // or = 0 or '\0';
       */
      printf("= %ld (IP:%s)\n", results.sum, results.in_addr);
  }
}