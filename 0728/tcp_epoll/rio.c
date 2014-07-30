#include "rio.h"

void rio_init(rio_t *rp, int fd)
{
    rp->fd_ = fd;
    rp->left_ = 0;
    rp->bufptr_ = rp->buff_;
}//初始化结构体

ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n)
{
    ssize_t nread;
    while(rp->left_ <= 0)
    {
        nread = read(rp->fd_, rp->buff_, sizeof(rp->buff_));//缓冲区空则将缓冲区读满
        if(nread == -1)
        {
            if(errno == EINTR)
                continue;
            return -1;
        }else if(nread == 0)
            return 0;
        rp->left_ = nread; 
        rp->bufptr_ = rp->buff_;  
    }

    int cnt = n;
    if(rp->left_ < n)
        cnt = rp->left_;
    memcpy(usrbuf, rp->bufptr_, cnt);
    rp->left_ -= cnt;
    rp->bufptr_ += cnt;
    return cnt;
}//从结构体中的数组复制n个字节，如果nleft<n则复制nleft字节，结构体中的数组为空，则从缓冲区读到结构体数组中

ssize_t rio_readn(rio_t *rp, char *usrbuf, size_t n)//从rp结构体中的字符数组中读取n个字节
{
    size_t nleft = n;
    ssize_t nread;
    char *bufp = usrbuf;

    while(nleft > 0)
    {
        if((nread = rio_read(rp, bufp, nleft)) < 0)
        {
            if(errno == EINTR)
                nread =0;
            return -1;
        }else if(nread == 0)
            break;
        nleft -= nread;
        bufp += nread;
    }
    return (n-nleft);
}

ssize_t rio_writen(int fd, char *usrbuf, size_t n)
{//写入n个字节
    size_t nleft = n;
    ssize_t nwritten;
    char *bufp = usrbuf;

    while(nleft > 0)
    {
        if((nwritten = write(fd, bufp, n)) < 0)
        {
            if(errno == EINTR)
                nwritten = 0;
            return -1;
        }
        nleft -= nwritten;
        bufp += nwritten;
    }
    return n;
}

ssize_t rio_readline(rio_t *rp, char *usrbuf, size_t maxlen)
{//读取一行
    char c, *buf = usrbuf;
    int n, cnt;

    for(n = 1; n < maxlen; n++)
    {
        if((cnt = rio_read(rp, &c, 1)) == 1)
        {
            *buf++ = c;
            if(c == '\n')
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





