void sigChld(int signo){
  int status;
  pid_t pid;
  while( (pid = waitpid(-1, &status, WNOHANG)) >0)
    printf("child %d terminated\n", pid);
  return;
}