/**
 * @note OPEN_MAX is intentionally not defined because it is no longer
 *  constant in Linux, it is runtime changeable.
 *  Use sysconf(_SC_OPEN_MAX) to query the same information.
 */
#include <unistd.h>
long sysconf(int nm)

/**
 * like settimeout() in JS. schedule an alarm signal. cause the system to 
 *  generate a SIGALRM signal for the process after the number of realtime 
 *  seconds specified by seconds have elapsed. Processor scheduling delays may
 *  prevent the process from handling the signal as soon as it is generated.
 * @param unsigned sec 0 on no new alarm() is scheduled; others on any previously
 *  set alarm() is canceled
 * @return unsigned >0 the seconds remaining until any previously scheduled 
 *  alarm was due to be delivered; 0 on no previously scheduled alarm
 * @example 
 *  static void fun(int signo){
 *    printf("Do it\n");
 *    alarm(1); // reset alarm(1)  like interval() in JS
 *  }
 *  signal(SIGALRM, fun);
 *  alarm(2);   // --> alarm() can only run one time  
 *  for(i=0; i<20; ++i){
 *    printf("sleep %d\n", i);
 *    sleep(1);
 *  }
 */
unsigned alarm(unsigned sec)