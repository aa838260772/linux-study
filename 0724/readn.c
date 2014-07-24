#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

ssize_t rio_readn(int fd, void *userbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nread;
    char *bufp = userbuf;

    while(nleft > 0)
    {
        if((nread = read(fd, bufp, nleft)) < 0)
        {
            if(nread == EINTR)
                nread = 0;
            else
                return -1;
        }else if(nread == 0)
            break;
        nleft -= nread;
        bufp += nread;
    }
    return (n - nleft);
}

int main(int argc, const char *argv[])
{
    char buf[1024];
    int fd = open("1.txt", O_RDONLY);
    int readn;
   readn =  rio_readn(fd, buf, 10);//
   printf("%d\n", readn) ;
   printf("%s\n", buf);
   close(fd);
   return 0;
}
