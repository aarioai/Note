int listenfd;
vDebug("socket()",
  listenfd = socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP)
);
struct sockaddr_in cli_addr, serv_addr;
memset(&serv_addr, 0, sizeof(serv_addr));
memset(&cli_addr, 0, sizeof(cli_addr));
serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
serv_addr.sin_port = htons(SERV_LISTEN_PORT);
vDebug("bind()",
  bind(listenfd, (const struct sockaddr *)&serv_addr, sizeof(serv_addr))
);

struct sctp_event_subscribe event_opt;
memset(&event_opt, 0, sizeof(event_opt));
event_opt.sctp_data_io_event = 1;
vDebug("setsockopt()",
  setsockopt(listenfd, IPPROTO_SCTP, SCTP_EVENTS, &event_opt, sizeof(event_opt))
);
vDebug("listen()",
  listen(listenfd, SERV_LISTEN_QUEUES)
);

struct args args;
struct results results;
struct sockaddr_in cli_addr;
struct sctp_sndrcvinfo sri;
int msg_flags;
socklen_t len;
for(;;){
  len = sizeof(cli_addr);
  vDebug("sctp_recvmsg()",
    sctp_recvmsg(listenfd, &args, sizeof(args),
      (struct sockaddr *)&cli_addr, &len,
      &sri, &msg_flags
    )
  );
  vDebug("sctp_sendmsg()",
    sctp_sendmsg(listenfd, &results, sizeof(results),
      (struct sockaddr *)&serv_addr, sizeof(serv_addr),
      sri.sinfo_ppid,
      sri.sinfo_flags, sri.sinfo_stream,
      0,0
    )
  );
}