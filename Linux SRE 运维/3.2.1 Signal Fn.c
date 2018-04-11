#include <sys/types.h>

/**

 */

/**
 * @see http://en.wikipedia.org/wiki/Unix_signal
 * Unix signals are normally not queued
 * Simplify:
 *  typedef void Sig(int);
 *  Sig * signal(int signo, Sig *func){}
 *  typedef void (*Sig)(int);
 *  Sig signal(int signo, Sig func){}
 * @param int signo
 *  SIGHUP hangup be sent to a process when its controlling terminal is closed
 *  SIGCHLD be sent to a parent process when a child process terminates, is 
 *    interrupted, or resumes[rɪ'zju:m] after being interruped.
 *  SIGPIPE be sent to a process when it attempts to write to a pipe without a process
 *    connected to the other end. be sent to the process When a process writes 
 *    to a socket that has received an RST. The default action of SIGPIPE is to
 *    terminate the process. If the process ignores SIGPIPE, returns EPIPE
 *  SIG_IGN
 *  SIG_DEL
 */
#include <signal.h>
void (*signal(int signo, void(*func)(int)))(int){
    struct sigaction act, old_act;
    act.sa_handler = func;
    sigmeptyset(&act.sa_mask);
    act.sa_flags = 0;
    if (signo == SIGALRM){
        #ifdef SA_INTERRUPT
            act.sa_flags |= SA_INTERRUPT;
        #endif
    } else {
        #ifdef SA_RESTART
            act.sa_flags |= SA_RESTART;
        #endif
    }
    if(sigaction(signo, &act, &old_act) < 0)
        return SIG_ERR;
    return old_act.sa_handler;
}



/**
 *
 */
struct sigaction {
    void (*sa_handler)(int);
    void (*sa_sigaction)(int, siginfo_t *, void *);
    sigset_t sa_mask;
    int sa_flags;
    void (*sa_restorer)(void);
}

/**
 * Examine and change a signal action
 * @param int signo specifies the signal and can be any valid signal except
 *  SIGKILL and SIGSTOP.
 * @param const struct sigaction *act if non-NULL, the new action for signal 
 *  signo is installed from act
 * @param struct sigaction *old_act if non-NULL, the previous action is saved
 *  in old_act
 */
int sigaction(int signo, 
    const struct sigaction *act, 
    struct sigaction *old_act
);



#include <sys/wait.h>
/**
 * Suspends execution until one of its children terminates
 * wait(&status_ptr) is equaivalent to waitpid(-1, &status_ptr, 0)
 * Unix signals are normally not queued, so wait() is worthless to 
 *  concurrent server. Which means, if there're N socket clients connect to 
 *  a server which'll fork() N childs. If the client and server are on the 
 *  same host, the signal handler is executed once, leaving (N-1) zombies;
 *  If on different host, the signal is executed twice or more times. So, we
 *  use waitpid(-1, int *status_ptr, WNOHANG) in a loop instead.
 * @return pid_t pid of child on success; -1 on error
 */
pid_t wait(int *status_ptr);
/**
 * @param pid_t pid 
 *  >0  it specifies the pid of a child process for which status is requested
 *  0  status is requested for any child process whose process group ID is equal to that of the calling process 
 *  -1  status is requested for any child process. In this respect, waitpid() is
 *      then equivalent to wait().
 *  <-1 status is requested for any child process whose process group ID is equal to the absolute value of pid.
 * @param int *status_ptr a value-result
 * @param int opt bitwise-inclusive OR of zero or defined in the <sys/wait.h>
 *  WNOHANG waitpid() not block (suspend execution of the calling thread) if
 *      there're runing children that have not yet terminated
 *  WCONTINUED
 *  WUNTRACED
 * @return pid_t the pid of teminated child
 *  int *status_ptr status of the terminated child
 * 我们先来看一个waitpid()的经典例子：当我们下载了A软件的安装程序后，在安装快结束时它又启动了另外一个流氓软件安装程序B，当B也安装结束后，才告诉你所有安装都完成了。A和B分别在不同的进程中，A如何启动B并知道B安装完成了呢？可以很简单地在A中用fork启动B，然后用waitpid()来等待B的结束。
 */
pid_t waitpid(pid_t pid, int *status_ptr, int opt);
/**
 * 
 */
int waitid(idtype_t idtype, id_t id, siginfo_t *siginf, int opt);

#include <fcntl.h>

int fcntl(int fd, int cmd, ...)



















