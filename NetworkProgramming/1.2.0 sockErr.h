#include	<stdarg.h>
#include	<syslog.h>
/**
 * Set it to be nonzero in daemon initial functions
 */
int ERR_IN_DAEMON_PROCESS;

/**
 * Interface 
 *  arguments must be: (const char *formated_msg, ...)
 */
static void errHandle(int, int, const char *, va_list);

/**
 * Fatal error related to system call, e.g. error in call a system function
 * @example
 *  execl("/bin/ls", "ls", "-al", "/etc/paswd", (char *)0);
 *  errSys("execl(%s)", "/bin/ls");  // or errSys("execl()");
 */
void err(int append_strerror, int syslog_prio, const char *formated_msg, ...){
  va_list ap;
  va_start(ap, formated_msg);
  errHandle(append_strerror, syslog_prio, formated_msg, ap);
  va_end(ap);
  exit(1);
}
void err_exit(const char *formated_msg, ...){
  va_list ap;
  va_start(ap, formated_msg);
  errHandle(errno, LOG_ERR, formated_msg, ap);
  va_end(ap);
  exit(1);
}
/**
 *
 */
void excp(int append_strerror, int syslog_prio, const char *formated_msg, ...){
  va_list ap;
  va_start(ap, formated_msg);
  errHandle(append_strerror, syslog_prio, formated_msg, ap);
  va_end(ap);
}

/**
 * Daemon Process with syslog()
 */
static void errHandle(int append_strerror, int syslog_prio, const char *formated_msg, va_list ap){
  char buf[SERV_BUF_SIZE + 1];    // defined in sock.h
  vsnprintf(buf, SERV_BUF_SIZE, formated_msg, ap);
  if(append_strerror){
    int n = strlen(buf);
    snprintf(buf+n, SERV_BUF_SIZE - n, " errno:%d(%s)", errno, strerror(errno));
  }
  strcat(buf, "\n");
    
  /**
   * Since a daemon does not have a controlling terminal, it cannot just fprintf
   *  to stderr. Using syslog() instead
   */
  if(ERR_IN_DAEMON_PROCESS)
    syslog(syslog_prio, buf);
  else{
    /**
     * If stderr is not stdout
     *  fflush(stdout);// flush stdout, otherwise it'l display later than stderr
     *  fputs(buf, stderr);     // without buffer
     * If stderr is stdout
     *  fputs(buf, stderr);
     *  fputs(stdout); or fputs(stderr);
     */
    fflush(stdout);
    fputs(buf, stderr);
    fflush(stderr);
  }
}