#include <signal.h>
/**
 * If a process terminates with children in the zombie state, the ppid of all 
 *  the zombie children is set to 1 (the init process). To clean the zombies, we
 *  establish a signal handler to catch SIGCHLD, and within the handler, we call
 *  wait().
 * @see C++/1.1.3 functors - function objects
 *  Common funct and SMF are all func-ptr, they're diff with a functor.
 * @param void (*func)(int);  func = sigChld;
 * @return void() struct sigaction.sa_handle on success; SIG_ERR on error
 *  signal(SIGCHLD, sigChld)() <=====>  sigaction.sa_handle();
 */
signal(SIGCHLD, sigChld);

void sigChld(int signo){
    pid_t pid;
    int status;
    /**
     * Unix signals are normally not queued, so wait() is worthless to 
     *  concurrent server. Which means, if there're N socket clients connect to 
     *  a server which'll fork() N childs. If the client and server are on the 
     *  same host, the signal handler is executed once, leaving (N-1) zombies;
     *  If on different host, the signal is executed twice or more times. So, we
     *  use waitpid() instead.
     */
    while ( (pid = waitpid(-1, &status, WNOHANG)) >0);
}
 