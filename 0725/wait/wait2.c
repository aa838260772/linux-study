//通过数组有序回收子进程的资源
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
#define N 10

int main(int argc, const char *argv[])
{
    int status,i;
    pid_t pid[10], rpid;

    for(i = 0; i < N; ++i)
        if((pid[i] = fork()) < 0)
        {
        perror("fork");
        exit(EXIT_FAILURE);
        }else if (pid[i] ==0)
        {
            printf("%d\n", getpid());
            exit(100 + i);
        }

     i = 0;
    while( (rpid = waitpid(pid[i], &status, 0)) > 0)
    {
    if(WIFEXITED(status))
        printf("child %d terminatede normally with exit status = %d\n",
                                    rpid, WEXITSTATUS(status));
    else
        printf("child %d terminatede abnormally\n", rpid);    
    i++;
    }

    if(errno != ECHILD)
    {
     perror("wait_pid error");
     exit(EXIT_FAILURE);
    }
    return 0;
}

