//readn writen 以及readline所在的头文件
#ifndef _RIO_H_
#define _RIO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#define MAXLINE 1024
#define RIO_BUFFER 8192

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

typedef struct
{
int fd_;
int left_;
char *bufptr_;
char buff_[RIO_BUFFER];
}rio_t;

void rio_init(rio_t *, int);
ssize_t rio_read(rio_t *, char *,size_t);
ssize_t rio_readn(rio_t *, char*, size_t);
ssize_t rio_writen(int, char*, size_t n);
ssize_t rio_readline(rio_t*, char*, size_t);
#endif /*RIO_H*/ 
