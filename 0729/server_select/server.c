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
#include <sys/select.h>
#define MAXLEN 1024

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int listenf();//封装了网络socket的socekt,bind,listen函数，返回监听的socket描述符
void handle(int signum)//SIGPIPE（子进程结束）的信号的处理
{
    printf("hello\n");
}
static void do_select(int);

int main(int argc, const char *argv[])
{
    if(signal(SIGPIPE, handle) == SIG_ERR)
        ERR_EXIT("signal");
    int listenfd = listenf();
    do_select(listenfd);
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

void do_select(int fd)
{
    //struct sockaddr_in cliaddr;
    //memset(&cliaddr, 0, sizeof(cliaddr));//此处不需要客户端的地址信息
    fd_set set;
    fd_set rset;
    FD_ZERO(&rset);
    FD_SET(fd, &rset);
    int nready;
    int fd_set[MAXLEN];

    int i;
    for(i = 0;i < MAXLEN; ++i)
        fd_set[i] = -1;
    fd_set[0] = fd;

    int maxi = fd;//初始最大轮询fd是监听的fd
    int  arrlen = 1;//表示数组长度
   
   char recvbuf[1024] = {0};
    while(1)
    {
        set = rset;
        nready = select(maxi+1, &set, NULL, NULL, NULL);
        if(nready == -1)
        {
            ERR_EXIT("select");
        }
        if(FD_ISSET(fd, &set))//查看书否有新的客户端请求
        {
            int clifd = accept(fd, NULL, NULL);
            if(clifd == -1)
                ERR_EXIT("accept");
            for(i = 1; i < MAXLEN; ++i)
            { if(fd_set[i] == -1)
                {
                    fd_set[i] = clifd;
                    break;
                }
            }
            FD_SET(clifd, &rset);
            if(clifd > maxi)
                maxi = clifd;
            arrlen++;
            --nready;
        }

        for(i = 1; i < arrlen; ++i)//轮询数据连接
        {
            int set_fd = fd_set[i];
         if(FD_ISSET(set_fd, &set))
         {
            int n = read(set_fd, recvbuf, 1024);
            if(n == -1)
                ERR_EXIT("read");
            else if(n == 0)//客户端退出，
            {
              FD_CLR(set_fd, &rset);
              close(set_fd);
              fd_set[i] = -1;
              arrlen--;
            }
            write(set_fd, recvbuf, strlen(recvbuf));
               memset(recvbuf, 0, 1024);
         if(--nready < 0)
             break;
         }
        }
    }
}


