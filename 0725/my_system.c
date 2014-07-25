//system命令实现过程：1.fork子进程，2.子进程中execl执行命令
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#define ERR_EXIT(m) \
    do{ \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int my_system(const char *command)
{
    pid_t pid ;
    if(command == NULL )
        return 1;
    int status;

    if((pid = fork()) < 0)
        ERR_EXIT("fork");
    else if(pid == 0)
    {
        execl("/bin/sh", "sh", "-c", command, NULL);//sh 一种shell格式， -c 命令 
        exit(EXIT_FAILURE);
    }else
    {
        while(waitpid(pid, &status, 0) <0)
        {
            if(errno == EINTR)
            continue;
            status = -1;
            break;
        }
    }
    return status;
}

int main(int argc, const char *argv[])
{
    printf("enter main.......\n");
    my_system("ls");
    printf("leave main.....\n");
    return 0;
}













