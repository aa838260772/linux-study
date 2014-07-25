//实现信号量的重定义来处理
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

#define ERR_EXIT(m)\
    do {\
        perror(m);\
      exit(EXIT_SUCCESS);\
      }while(0)

typedef void (*signalhandler_t) (int);

void handler(int signum)
{
printf("Ctrl + c\n");
}

int main(int argc, const char *argv[])
{
    signalhandler_t old;
    if((old = signal(SIGINT, handler)) == SIG_ERR )
        ERR_EXIT("signal");
    if(signal(SIGQUIT, SIG_IGN) == SIG_ERR)//忽略信号量SIGQUIT
        ERR_EXIT("signal");
    for(;;)
        pause();//暂停程序，直到接收信号
    return 0;
}
