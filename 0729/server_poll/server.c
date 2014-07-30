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
#include <signal.h>
#include <poll.h>
#define MAXLEN 1024

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

static void do_service(int);
int listenf();
void handle(int signum)
{
    printf("hello\n");
}
static void do_poll(int);

int main(int argc, const char *argv[])
{
    if(signal(SIGPIPE, handle) == SIG_ERR)
        ERR_EXIT("signal");
    int listenfd = listenf();
    do_poll(listenfd);
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

void do_poll(int fd)
{
    struct pollfd pfd[MAXLEN];//设置的最大连接数，存放结构体信息
    char recvbuf[1024] = {0};
    int i;
    for(i = 0; i < MAXLEN; ++i)
        pfd[i].fd = -1;

    pfd[0].fd = fd;
    pfd[0].events = POLLIN;//将监听连接的描述符防止数组开头

    int nready;
    int maxi = 0;
    while(1)
    {
        nready = poll(pfd, maxi+1, -1);//轮询的是有效数组长度，不能少1
        if(nready == -1)
        {
            ERR_EXIT("select");
        }

        if(pfd[0].revents & POLLIN)//有客户端请求连接
        {
            int clifd = accept(fd, NULL, NULL);
            if(clifd == -1)
                ERR_EXIT("accept");
            for(i = 1; i < MAXLEN; ++i)
            { 
                if(pfd[i].fd == -1)
                {
                    pfd[i].fd = clifd;
                    pfd[i].events = POLLIN;
                    break;
                }
            }
            if(i > maxi)
                maxi = i;  
            --nready;
        }

        for(i = 1; i <= maxi; ++i)
        {
            if(pfd[i].fd == -1)
                continue;

            if( pfd[i].revents & POLLIN)
            {
                int n = read(pfd[i].fd, recvbuf, 1024);
                if(n == -1)
                    ERR_EXIT("read");
                else if(n == 0)//客户端退出,则从集合中清除
                {
                    printf("%d close\n", pfd[i].fd);
                    close(pfd[i].fd); 
                    pfd[i].fd = -1;
                    continue;
                }
                write(pfd[i].fd, recvbuf, strlen(recvbuf));
                memset(recvbuf, 0, 1024);

                if(--nready < 0)
                    break;
            }
        }
    }
}

