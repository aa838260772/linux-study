#include "rio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

static void do_client(int fd)
{
    char recvbuf[MAXLINE + 1] = {0};
    char sendbuf[MAXLINE + 1] = {0};

    int epollfd = epoll_create(2);//返回的也是一个文件描述符
    if(epollfd == -1)
        ERR_EXIT("epoll_create");

    struct epoll_event events[2];
    struct epoll_event ev;

    int ret;
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);//注册fd
    if(ret == -1)
        ERR_EXIT("epoll_ctl");

    ev.data.fd = fileno(stdin);
    ev.events = EPOLLIN;
    ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, STDIN_FILENO, &ev);//注册fd
    if(ret == -1)
        ERR_EXIT("epoll_ctl");

    int nready;

    while(1)
    {
        nready = epoll_wait(epollfd, events, 2, -1);
        if(nready < 0)
        {
            if(errno == EINTR)
                continue;
            ERR_EXIT("select");
        }else if(nready  ==  0)
        {
            continue;
        }

        int i;
        for(i = 0; i < nready; i++)    
        {
            int nfd = events[i].data.fd;
            if(nfd == STDIN_FILENO)
            {
                if(fgets(sendbuf, 1024, stdin) == NULL)
                {
                    shutdown(fd, SHUT_WR);
                    struct epoll_event ee;
                    ee.data.fd = STDIN_FILENO;
                    if(epoll_ctl(epollfd, EPOLL_CTL_DEL, STDIN_FILENO, &ee) == -1)
                        ERR_EXIT("epoll_ctl");
                }else
                    write(fd, sendbuf, strlen(sendbuf));
            }
            if(nfd == fd)
            {
                int ret = read(fd, recvbuf, 1024);
                if(ret == -1)
                    ERR_EXIT("readline");
                else if(ret == -1) 
                {
                    close(fd);
                    printf("fd close\n");
                    exit(EXIT_SUCCESS);
                }
                printf("recv data :%s\n", recvbuf);
            }
        }
    }
    memset(recvbuf, 0, sizeof recvbuf);
    memset(sendbuf, 0, sizeof sendbuf);
}

int main(int argc, const char *argv[])
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0)
        ERR_EXIT("socket");

    struct sockaddr_in cliaddr;
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(8888);
    cliaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    socklen_t len = sizeof cliaddr;

    int ret ;
    if((ret = connect(fd, (struct sockaddr*)&cliaddr, len)) == -1)
    {
        close(fd);
        ERR_EXIT("connect");
    }
    do_client(fd);
    close(fd);
    printf("123\n");
    return 0;
}
