#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "rio.h"
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
    int rcnt = 0;
    while(1)
    {
        memset(recvbuf, 0, sizeof recvbuf);
        // ret = rio_readn(&rt, recvbuf, 5);
        ret = rio_readline(&rt, recvbuf, 1024);
        //   rcnt++;
        // printf("%d message\n",rcnt);
        sleep(5);
        if(ret == -1)
        {
            if(errno == EINTR)
                continue;
            return ;
        }   
        else if(ret > 0)
            rio_writen(fd, recvbuf, 5);
     //   else
       //     break;
    }
}

int main(int argc, const char *argv[])
{
//      signal(SIGPIPE, SIG_IGN);
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);//准备一个socketfd
    if(listenfd == -1 )
        ERR_EXIT("listen");

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

    struct sockaddr_in cliaddr;
    bzero(&cliaddr, sizeof(cliaddr));
    socklen_t cli_len = sizeof cliaddr;

    int clientfd;
    clientfd = accept(listenfd, (struct sockaddr*)&cliaddr, &cli_len);

    if(clientfd == -1)  
    {
        close(listenfd);
        ERR_EXIT("accept");
    }
    do_service(clientfd);

    close(clientfd);
    close(listenfd);
    return 0;
}

