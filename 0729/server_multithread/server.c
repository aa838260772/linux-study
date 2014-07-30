/*selcet服务器客户端模型:
  1.客户端关闭后，服务器再向客户端发送信息，第一次会收到一个RST复位报文，第二次会收到SIGPIPE信号，导致服务器关闭，必须对这个信号进行处理：
  1.在服务器对read返回值为0的情况进行处理，不向客户端发送信息
  2.signal函数: signal(SIGPIPE, handle) 或者直接忽略signal(SIGPIPE, SIG_IGN)
  */
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
#include <pthread.h>

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
        ret = rio_readline(&rt, recvbuf, 1024);
         if(ret == 0)
         {
         close(fd);
//         break;
          pthread_exit(NULL);
         }
         write(fd, recvbuf, strlen(recvbuf)) ;
    }
}

void handle(int signum)
{
    printf("hello\n");
}

void *pthread_func(void *arg)
{
    pthread_detach(pthread_self());
    int *q = (int*)arg;
   int p = *(int*)arg;
   free(q);
     do_service(p);
     close(p);
}
int listenf();

int main(int argc, const char *argv[])
{
    if(signal(SIGPIPE, handle) == SIG_ERR)
        ERR_EXIT("signal");
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

    pthread_t tid;
    int *p = (int*)malloc(sizeof(int));
   *p = clientfd;
    pthread_create(&tid, NULL, pthread_func, p);
    }
    close(listenfd);
    return 0;
}

int listenf()
{
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
return listenfd;
}
