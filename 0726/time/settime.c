#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/time.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
void handle(int signum)
{
printf("signum:%d\n", signum);
}

int main(int argc, const char *argv[])
{
   if((signal(SIGALRM, handle)) == SIG_ERR)  
       ERR_EXIT("alarm");

   struct timeval tv_interval = {1, 0};
   struct timeval tv_value = {1, 0};
   struct itimerval it;
   it.it_interval = tv_interval;
   it.it_value = tv_value;
   setitimer(ITIMER_REAL, &it, NULL);
   for(;;)
       pause();

    return 0;
}
