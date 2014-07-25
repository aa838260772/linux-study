//无序回收子进程的资源
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
#define N 10

int main(int argc, const char *argv[])
{
    int status,i;
    pid_t pid;

    for(i = 0; i < N; ++i)
    {
        if((pid = fork()) < 0)
        {
        perror("fork");
        exit(EXIT_FAILURE);
        }else if (pid == 0)
        {
//            printf("%d\n", getpid());
            exit(100 + i);
        }
    }

    while( (pid = waitpid(-1, &status, 0)) > 0)
    {
    if(WIFEXITED(status))
        printf("child %d terminatede normally with exit status = %d\n" ,  
                pid, WEXITSTATUS(status));
    else
        printf("child %d terminatede abnormally\n", pid);    
    }

    if(errno != ECHILD)//最后的错误是 errno == ECHLD没有子进程等待了
    {
     perror("wait_pid error");
     exit(EXIT_FAILURE);
    }
    return 0;
}

