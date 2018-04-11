struct addrinfo hints, *ai, *ai4free;
memset(&hints, 0, sizeof(struct addrinfo));
hints.ai_flags = AI_CANONNAME;  // for ai->ai_canonname
hints.ai_family = AF_UNSPEC;
hints.ai_socktype = AF_STREAM;
int n;
if(0 != (n = getaddrinfo(host, service, &hints, &ai))){
  printf("getaddrinfo() error: %d(%s)", n, gai_strerror(n));
  exit(0);
}
ai4free = ai;

while(ai != NULL){
  printf("[ai] cn:%s ", ai->ai_canonname);
  printf("fm:%d st:%d pr:%d\n", ai->ai_family, ai->ai_socktype, ai->ai_protocol);
  switch(ai->ai_family){
    case AF_INET:{
      struct sockaddr_in i4 = *(struct sockaddr_in *)ai->ai_addr;
      char i4_str[INET_ADDR_STRLEN);
      printf("[i4] fm:%d pr:%d ", i4.sin_family. i4.sin_protocol);
      /**
       * @todo ip will always be 2.0.0.port
       */
      inet_ntop(i4.sin_family, &i4, i4_str, (socklen_t)INET_ADDR_STRLEN);
      printf("ip:%s", i4_str);
      } break;
    default:
      printf("unknown ai_family in switch(){}: %d", ai->ai_family);
      break;
  }
  ai = ai->next;
}
freeaddrinfo(ai4free);