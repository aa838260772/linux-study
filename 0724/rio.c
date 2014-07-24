/*
 *实现最小系统调用的readn,readline 和writen
 *很重要
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#define ERR_EXIT(m)\
    do { \
        perror(m); \
        exit(EXIT_FAILURE); \
    }while(0) \

#define MAXLINE 1024
#define RIO_BUFFER 8192
typedef struct
{
    int fd_;
    int left_;
    char *bufptr_;
    char buff_[RIO_BUFFER];
}rio_t;

void rio_init(rio_t *rp, int fd)
{
    rp->fd_ = fd;
    rp->left_ = 0;
    rp->bufptr_ = rp->buff_;
}//初始化结构体

ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n)
{
    ssize_t nread;
    while(rp->left_ <= 0)//缓冲区中没有内容时从文件中读，
    {
        nread = read(rp->fd_, rp->bufptr_, sizeof(rp->buff_));
        if(nread == -1)
        {
            if(errno == EINTR)
                continue;
            return -1;
        }else if(nread == 0)
            return 0;
        rp->left_ = nread;
        rp->bufptr_ = rp->buff_;//重置指针
    }
    int cnt = n;
    if(rp->left_ < n)
        cnt = rp->left_;//取两者较小值
    memcpy(usrbuf, rp->bufptr_, cnt);//从缓冲区中读内容到传进来的字符指针中
    rp->left_ -= cnt;//剩余缓冲区大小和指针都要变化
    rp->bufptr_  += cnt;
    return cnt;
}

ssize_t rio_readn(rio_t *rp, void  *usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nread;
    char *bufp = usrbuf;

    while(nleft > 0)//未读取一定数目的继续读，直到读取满足数目的字节
    {
        if((nread = rio_read(rp, bufp, nleft)) < 0)
        {
            if(errno == EINTR)
                nread = 0;//继续重新读
            else
                return -1;
        }
        else if(nread == 0)
            break;
        nleft -= nread;
        bufp += nread;
    }
    return (n - nleft);
}

ssize_t rio_writen(int fd, char *usrbuf, size_t n)
{//不用结构体，直接写入文件
    size_t  nleft = n;
    ssize_t nwritten;
    char *bufp = usrbuf;

    while(nleft > 0)
    {
        if((nwritten = write(fd, bufp, nleft)) < 0)
        {
            if(errno == EINTR)
                nwritten = 0;
            else
                return -1;
        }//write时不会返回值为0
        nleft -= nwritten;
        bufp += nwritten;
    }
    return n;
}

ssize_t rio_readline(rio_t *rp, void *usrbuf, size_t maxlen)
{
    char c, *buf = usrbuf;
    int n, cnt;

    for(n = 1; n < maxlen; n++)
    {//每次读取一个字符并判断，最后加个'\0',实现字符串的输出
        if((cnt = rio_read(rp, &c, 1)) == 1)
        {
            *buf++ = c;
            if(c == '\n')//找到一行末尾，退出
                break;
        }else if(cnt == 0)
        {
            if(n == 1)
                return 0;
            else
                break;
        }else
            return -1;
    }
    *buf = '\0';
    return n;
}

int main(int argc, const char *argv[])
{
    rio_t rp;
    int fd = open("1.txt", O_RDONLY);
    char buf[MAXLINE] = {0};

    rio_init(&rp, fd);
    rio_readn(&rp, buf, 10);
//    rio_readline(&rp, buf, 1024);
    printf("%s\n", buf);

    return 0;
}



