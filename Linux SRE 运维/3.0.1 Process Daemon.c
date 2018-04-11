#include "sock.h"
#include <signal.h>

/**
 *
 sh$ ps al | grep forklift.out
    F UID  PID  PPID PRI NI WCHAN  STAT TTY    CMD
    0 1000 5000 4000 76  0  hrtime S+   pts/0  ./forklift.out
    1 1000 5001 5000 75  0  exit   Z+   pts/0  [forklift.out] <defunct>
    0 1000 5002 3000 76  0  pipe_w S+   pts/0  ps
*/
#define MAXFD 64;

int daemonInit(const char *pnm, int facility){
  /**
   * @return pid_t 0 in child, process id of child in parent, -1 on error 
   */
  pid_t pid;
  int chld_status;
  if((pid = fork())<0){       // create a child process pid: 5001
      printf("fork error");
      return (-1);
  } else if(pid){                     // getpid()=5000; child pid=5001
      printf("Pid%d -> C%d\n", getpid(), pid);
      // pid = wait(&chld_status);      // terminates it's child
      // printf("child %d terminated\n", pid);
      _exit(0);    // parent terminates
  } 
  
  printf("Pid%d", getpid());    // getpid() = 5001, it's a child process
  
  if(setsid() < 0) // set session id error, now child process is detached from parent
    return (-1);
  signal(SIGHUP, SIG_IGN);
  
  if((pid = fork()) < 0)      // child process (now another group session leader)
    return (-1);
  else if(pid)
    _exit(0);           // child group session process terminates
  
  /**
   * Child (now is a parent process)'s child continues
   *  this process is no longer a session leader, so it can't acquire a control
   *    -ling terminal.
   *  这一步也是必要的步骤。使用fork创建的子进程继承了父进程的当前工作目录。由于
   *  在进程运行中，当前目录所在的文件系统（如“/mnt/usb”）是不能卸载的，这对以后
   *  的使用会造成诸多的麻烦（比如系统由于某种原因要进入单用户模式）。因此，通常
   *  的做法是让"/"作为守护进程的当前工作目录，这样就可以避免上述的问题，当然，
   *  如有特殊需要，也可以把当前工作目录换成其他的路径，如/tmp。改变工作目录的
   *  常见函数式chdir。
   */
  chdir("/");
  
  /**
   * 同文件权限码一样，用fork函数新建的子进程会从父进程那里继承一些已经打开了的文件。这些被打开的文件可能永远不会被守护进程读写，但它们一样消耗系统资源，而且可能导致所在的文件系统无法卸下。
在上面的第二步之后，守护进程已经与所属的控制终端失去了联系。因此从终端输入的字符不可能达到守护进程，守护进程中用常规方法（如printf）输出的字符也不可能在终端上显示出来。所以，文件描述符为0、1和2 的3个文件（常说的输入、输出和报错）已经失去了存在的价值，也应被关闭。通常按如下方式关闭文件描述符：
   */
  for(int i=0; i < MAXFD; ++i)
    close(i);               // close off any open descriptors
  open("/dev/null", O_RDONLY);
  open("/dev/null", O_RDWR);
  open("/dev/null", O_RDWR);
  openlog(pnm, LOG_PID, facility);
  
  return 0;
}

