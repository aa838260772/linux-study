#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#define N 10
#define ERR_EXIT(m)\
    do{\
        perror(m);\
        exit(EXIT_SUCCESS);\
    }while(0)

void handle(int signum)
{
    pid_t pid;
    while((pid = waitpid(-1, NULL, WNOHANG)) > 0)//有子进程时会阻塞等待接收完s所有子进程的sigchld信号
    {
        printf("handler process child %d\n", pid);
        sleep(2);
    }
}

int main(int argc, const char *argv[])
{
    if(signal(SIGCHLD, handle) == SIG_ERR)
        ERR_EXIT("signal");
    pid_t pid;

    int i;
    for(i = 0; i< N; ++i)
    {
        if((pid = fork()) < 0)
            ERR_EXIT("fork");
        else if(pid == 0)
        {
            printf("hello from child %d\n", getpid());
            sleep(2);
            exit(EXIT_SUCCESS);
        }
    }

    int n;
    char buf[1024];
    if((n = read(STDIN_FILENO, buf, 1000)) < 0)
        ERR_EXIT("read error");
    while(1);
    return 0;
}
