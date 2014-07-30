#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "rio.h"//封装了网络编程中的readn  writen   readline 3个函数
#include <signal.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

static void do_service(int fd)
{
    rio_t rt;
    rio_init(&rt, fd);
    char recvbuf[1024] = {0};
    int ret;
    while(1)
    {
        memset(recvbuf, 0, sizeof recvbuf);
        ret = rio_readline(&rt, recvbuf, 1024);
        if(ret == 0)   
        {
            close(fd);
            exit(EXIT_SUCCESS);
        }
        rio_writen(fd, recvbuf, strlen(recvbuf)) ;
    }
}

void handle(int signum)//对SIGCHLD信号的处理函数
{
    while(waitpid(-1, NULL, WNOHANG) > 0);
    return ;
}

int listenf();//封装了socket,bind,listen3个函数，返回需要监听的连接socket描述符

int main(int argc, const char *argv[])
{
    if(signal(SIGPIPE, SIG_IGN) == SIG_ERR)//对客户端关闭导致的信号的处理
        ERR_EXIT("signal_pipe");
    if(signal(SIGCHLD, handle) == SIG_ERR)//对子进程结束后资源的回收
        ERR_EXIT("signal_chld");


    int listenfd = listenf();

    struct sockaddr_in cliaddr;
    bzero(&cliaddr, sizeof(cliaddr));
    socklen_t cli_len = sizeof cliaddr;
    int clientfd;
    while(1)
    {
        clientfd = accept(listenfd, (struct sockaddr*)&cliaddr, &cli_len);
        if(clientfd == -1)  
        {
            close(listenfd);
            ERR_EXIT("accept");
        }
        
        int pid;
        if((pid = fork()) == -1)
        {
            ERR_EXIT("fork");
        }else if(pid == 0)
        {
            close(listenfd);
            do_service(clientfd);
            exit(EXIT_SUCCESS);
        }
        close(clientfd);
    }
    close(listenfd);
    return 0;
}

int listenf()
{
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);//准备一个socketfd
    if(listenfd == -1 )
        ERR_EXIT("socket");

    int on = 1;
    if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1)//setsockopt设置端口复用
    {
        close(listenfd);
        ERR_EXIT("setsockopt");
    }

    struct sockaddr_in seraddr;
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(8888);
    seraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    socklen_t len = sizeof(seraddr);
    if(bind(listenfd, (struct sockaddr*)&seraddr, len) == -1)//监听socket端口，
    {
        close(listenfd);
        ERR_EXIT("bind");
    }

    if(listen(listenfd, 6) == -1)
    {
        close(listenfd);
        ERR_EXIT("listen");
    }
    return listenfd;
}
