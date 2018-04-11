int
main(int argc, char **argv)
{
    int                    fd;
    socklen_t            len;
    struct sock_opts    *ptr;

    for (ptr = sock_opts; ptr->opt_str != NULL; ptr++) {
        printf("%s: ", ptr->opt_str);
        if (ptr->opt_val_str == NULL)
            printf("(undefined)\n");
        else {
            switch(ptr->opt_level) {
            case SOL_SOCKET:
            case IPPROTO_IP:
            case IPPROTO_TCP:
                fd = Socket(AF_INET, SOCK_STREAM, 0);
                break;
#ifdef    IPV6
            case IPPROTO_IPV6:
                fd = Socket(AF_INET6, SOCK_STREAM, 0);
                break;
#endif
#ifdef    IPPROTO_SCTP
            case IPPROTO_SCTP:
                fd = Socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP);
                break;
#endif
            default:
                err_quit("Can't create fd for level %d\n", ptr->opt_level);
            }

            len = sizeof(opt_val);
            if (getsockopt(fd, ptr->opt_level, ptr->opt_name,
                           &opt_val, &len) == -1) {
                err_ret("getsockopt error");
            } else {
                printf("default = %s\n", (*ptr->opt_val_str)(&opt_val, len));
            }
            close(fd);
        }
    }
    exit(0);
}
