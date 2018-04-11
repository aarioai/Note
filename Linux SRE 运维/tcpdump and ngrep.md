* http://www.tcpdump.org/manpages/tcpdump.1.html


# Connected by Local
```
53004                              9501
        -- [SYN] seq x177 -->
       <-- [SYN] seq y084, ack x178 --
        --  [.]  ack 1 -->
        -- [PUSH 36: seq 1:37, ack 1] eyJ0byI6MCwibXNnIjoiUVdGeWFXOD0ifQ== ->
       <-- [.    ack 37] --
       <-- [PUSH 48: seq 1:49, ack 37] eyJ0byI6MCwibXNnIjoiUVdGeWFXOD0iLCJmcm9tIjoxfQ==
        --  [.   ack 49] -->
        



sh$ tcpdump -i lo port 9501
|[
    tcpdump: verbose output suppressed, use -v or -vv for full protocol decode
    listening on lo, link-type EN10MB (Ethernet), capture size 65535 bytes
    16:35:09.540470 IP localhost.53004 > localhost.9501: Flags [S], seq 211043177, win 43690, options [mss 65495,sackOK,TS val 21662677 ecr 0,nop,wscale 7], length 0
    04:34:49.745341 IP localhost.9501 > localhost.53004: Flags [S.], seq 2538132084, ack 211043178, win 43690, options [mss 65495,sackOK,TS val 21662677 ecr 21662677,nop,wscale 7], length 0
    16:35:09.540505 IP localhost.53004 > localhost.9501: Flags [.], ack 1, win 342, options [nop,nop,TS val 21662677 ecr 21662677], length 0
    16:35:09.540714 IP localhost.53004 > localhost.9501: Flags [P.], seq 1:37, ack 1, win 342, options [nop,nop,TS val 21662678 ecr 21662677], length 36
    16:35:09.540722 IP localhost.9501 > localhost.53004: Flags [.], ack 37, win 342, options [nop,nop,TS val 21662678 ecr 21662678], length 0
    16:35:09.541145 IP localhost.9501 > localhost.53004: Flags [P.], seq 1:49, ack 37, win 342, options [nop,nop,TS val 21662678 ecr 21662678], length 48
    16:35:09.541155 IP localhost.53004 > localhost.9501: Flags [.], ack 49, win 342, options [nop,nop,TS val 21662678 ecr 21662678], length 0
]|



sh$ ngrep -d lo '' 'port 9501'
|[
    interface: lo (127.0.0.0/255.0.0.0)
    filter: ( port 9501 ) and (ip or ip6)
    ####
    T 127.0.0.1:53004 -> 127.0.0.1:9501 [AP]
      eyJ0byI6MCwibXNnIjoiUVdGeWFXOD0ifQ==
    ##
    T 127.0.0.1:9501 -> 127.0.0.1:53004 [AP]
      eyJ0byI6MCwibXNnIjoiUVdGeWFXOD0iLCJmcm9tIjoxfQ==
    #
]|
```

# Connected by Remote
```

sh$ sudo ngrep '[a-zA-Z]' -t -W byline -qp -d any port 9501
```