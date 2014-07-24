#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

#define ERR_EXIT(m)\
    do\
{\
    perror(m);\
    exit(EXIT_FAILURE);\
}while(0)

void setblock(int fd);//将文件描述符设置为阻塞
void setnonblock(int fd);//将文件描述符设置为阻塞
int main(int argc, const char *argv[])
{
    //  int fd = open("1.txt", O_WRONLY | O_APPEND);
    // if(fd == -1)
    //    ERR_EXIT("open");
    setnonblock(0);
    char buf[1024];
    setblock(0);

    read(0, buf, 1024);
    write(1, buf, strlen(buf));
    return 0;
}

void setnonblock(int fd)
{
    int val;
    val = fcntl(fd, F_GETFL, 0);
    if(val == -1)
        ERR_EXIT("fcntl:");
    val |= O_NONBLOCK;
    fcntl(fd, F_SETFL, val);
}

void setblock(int fd)
{
    int val;
    val = fcntl(fd, F_GETFL, 0);
    if(val == -1)
        ERR_EXIT("fcntl:");
    val &= ~O_NONBLOCK;
    fcntl(fd, F_SETFL, val);
}





