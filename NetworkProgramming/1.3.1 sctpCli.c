int sockfd;
vDebug("socket()",
  sockfd = socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP)
);

struct sctp_event_subscribe event_opt;
memset(&event_opt, 0, sizeof(event_opt));
event_opt.sctp_data_io_event = 1;
vDebug("setsockopt()",
  setsockopt(sockfd, IPPROTO_SCTP, SCTP_EVENTS, &event_opt)
);

struct sockaddr_in peer_addr, serv_addr;
memset(&serv_addr, 0, sizeof(serv_addr));
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htos(SERV_LISTEN_PORT);
inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

struct args args;
struct results results;
char sendbuf[SERV_BUF_SIZE];
struct sndrcvinfo sri;
int msg_flags;
socklen_t len;
while(fgets(sendbuf, SERV_BUF_SIZE, stdin)){
  /**
   * int streamno:string msg
   */
  if(3 != sscanf(sendbuf, "%d:%ld %ld", &sri.sinfo_stream, &args.arg1, &args.arg2)){
    printf("please input 'int streamno:int arg1 int arg2'");
    continue;
  }

  vDebug("sctp_sendmsg()",
    sctp_sendmsg(sockfd, &args, sizeof(args),
      (const struct sockaddr *)&serv_addr, sizeof(serv_addr),
      0, 0, sri.sinfo_stream, 0, 0
    );
  );
  len = sizeof(peer_addr);
  vDebug("sctp_recvmsg()",
    sctp_recvmsg(sockfd, &results, sizeof(results),
      (struct sockaddr *)&peer_addr, &len,
      &sri, &msg_flags
    )
  );
  printf("%hd: %ld+%ld=%ld", sri.sinfo_stream, args.arg1, args.arg2, results.sum);
  printf("(ssn %d; assock_id 0x%x)\n", sri.sinfo_ssn, (u_int) sri.sinfo_assoc_id);
  
}