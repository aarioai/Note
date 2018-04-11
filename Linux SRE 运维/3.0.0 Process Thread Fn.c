#include <unistd.h>
#include <syslog.h>

/**
 * @return 
 *  >0 in parent; the pid of its child process; 
 *  0  in child; getpid() returns its pid
 *  -1 in parent with errno, no child process is created
 * @note The child has a single thread and inherits copies of the parent's set of 
 *  open file descriptors: the child and parent share 
 *    open file status flags
 *    current file offset
 *    signal-driven I/O attr.
 *  open queue descriptors:
 *  open directory streams: 
 */
pid_t fork()

/**
 * Terminate
 * @param/return int status C specifies EXIT_SUCESS and EXIT_FAILURE
 *  it is returned to its parent with a status &0377, can be collected with wait()
 */
void exit(int status)
/**
 * Terminate immediately, any open fds belonging to the process are closed; any 
 *  children are inherited by process 1, init, and its parent is sent a SIGCHLD
 * @param/return int status is returned to its parent 
 */
void _exit(int status)

#include <sys/wait.h>
/**
 * wait if exited
 * @return int true if the child terminated with exit(), _exit() or by returning
 *    from main()
 */
#define WIFEXITED(int status)
/**
 * wait exit status
 * @return int the exit status of the child
 * @note this macro should only be employed if WIFEXITED(status) returned true
 */
#define WEXITSTATUS(int status)
pid_t wait(int *status)
/**
 * Pause process and waiting for signal or terminates of a child process
 * @param/return int *status
 * @param int opts 0 or more that split with OR
 *  WNOHANG return 0 immediately if no child has exited or child's pid on exited
 * @return int pid wait for
 *  <-1 any child whose GID equals abs(pid)
 *  -1  any child
 *  0   any child whose GID equals the calling process
 *  >0  the child with this PID
 */
pid_t waitpid(pid_t pid, int *status, int opts)
int waitid(idtype_t idtype, id_t id, siginfo_t *info, int opts)
pid_t getpid()    // the PID of the calling process
pid_t getppid()   // the PID of the parent of the calling process


/**
 * Create a session and set it to the process group ID
 * @return pid_t the new session ID on success; -1 with errno on error
 * 由于创建守护进程的第一步调用了fork函数来创建子进程，再将父进程退出。由于在调用了fork函数时，子进程全盘拷贝了父进程的会话期、进程组、控制终端等，虽然父进程退出了，但会话期、进程组、控制终端等并没有改变，因此，这还不是真正意义上的独立开来，而setsid函数能够使进程完全独立出来，从而摆脱其他进程的控制。
 */
pid_t setsid()

/**
 * Since a daemon does not have a controlling terminal, it cannot just fprintf
 *  to stderr. Using syslog() instead
 * @param prio combines a level and a facility
 *  level
 *    0 LOG_EMEG
 *    1 LOG_ALERT
 *    2 LOG_CRIT
 *    3 LOG_ERR
 *    4 LOG_WARNING
 *    5 LOG_NOTICE
 *    6 LOG_INFO
 *    7 LOG_DEBUG
 *  facility
 *    LOG_AUTH security/authorization messages
 *    LOG_AUTHPRIV security/authorization messages(private)
 *    LOG_CRON cron daemon
 *    LOG_DAEMON
 *    LOG_FTP
 *    LOG_KERN
 *    LOG_LOCAL0
 *    ..
 *    LOG_LOCAL7
 *    LOG_LPR line printer system
 *    LOG_MAIL
 *    LOG_NEWS
 *    LOG_SYSLOG
 *    LOG_USER
 *    LOG_UUCP 
 * @example syslog(LOG_INFO | LOG_LOCAL2, "re(%s, %s):%m", file1, file2); 
 * @note In CentOS 7, syslogd 's configure file is /etc/rsyslog.conf
 *  If the daemone receives the SIGHUP signal, it rereads its configuration file
 *  The messages will be probably saved in /var/log
 *  
 */
void syslog(int prio, const char *msg, ...)
/**
 * it can be perpended or appended to syslog()
 * @param int opts
 *  LOG_CONS
 *  LOG_NDELAY
 *  LOG_PERROR
 *  LOG_PID
 */
void openlog(const char *ident, int opts, int facility)
void close()

/**
 * exec list: Replace the current process image with a new process image
 * @param const char *arg must be terminated by a (char *)0 or (char *)NULL.
 * @return -1 only on error
 * @example
 *  ls -al /etc/passwd
 *    execl("/bin/ls", "ls", "-al", "/etc/passwd", (char *)0)
 *  /provoke.out
 *    execl("/provoke.out", "provoke.out", (char *)0)
 */
int execl(const char *path, const char *arg1, const char *arg2, ..., const char * NULL)
