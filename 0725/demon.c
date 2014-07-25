//创建守护进程1.fork子进程，让父进程先退出 2.标准输入输出错误定向到/dev/null不显示到屏幕上
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#define ERR_EXIT(m) \
    do{ \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int main(int argc, const char *argv[])
{
    pid_t pid;
    if((pid = fork()) < 0)
        ERR_EXIT("fork");
    else if(pid > 0)
        exit(EXIT_SUCCESS);

    setsid();//创建一个新的会话，脱离shell的会话期，
    chdir("/");//更改工作目录
    umask(0);

     int  fd = open("/dev/null", O_WRONLY);
    if(fd == -1)
        ERR_EXIT("open");
    dup2(fd, STDIN_FILENO);
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);
   close(fd);
    while(1);
    return 0;
}

