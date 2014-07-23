#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE); \
    }while(0)
void prin(int fd)
{
    char buf[1024];
    while(memset(buf,0,sizeof(buf)), read(fd, buf, 1024) )
    {
        write(1, buf, strlen(buf));
    }
}

void scan(int fd)
{
    char buf[1024];
    while(bzero(buf, 0), fgets(buf, 1024, stdin) != NULL )
    {
        write(fd, buf, strlen(buf));
    }
}

int main(int argc, const char *argv[])
{
    //打开文件读，不存在返回错误信息并退出
    int fd = open("1.txt", O_RDONLY);
   //1. int fd2 = dup(fd);
   //2.     int fd2 = 5;
   //   dup2(fd, fd2);
      int fd2 = fcntl(fd, F_DUPFD, 0);
    if(fd == -1)
        ERR_EXIT("open");
    printf("%d\n", fd);
    prin(fd);
    close(fd);

    //以追加方式写入文件，不加追加方式则会从文件开头写起，覆盖原有的位置
    /*    fd = open("1.txt", O_WRONLY | O_APPEND);
          if(fd == -1)
          ERR_EXIT("open");
          scan(fd);
          close(fd);

          fd = open("1.txt", O_RDONLY);
          if(fd == -1)
          ERR_EXIT("open");
          prin(fd);
          close(fd);
          return 0;
    fd = open("1.txt", O_RDONLY);
    fseek(fdopen(fd, "rb"), 10, SEEK_SET);
    prin(fd);
    close(fd);
    */
    //重定向
    printf("fd2:%d\n", fd2);
    fseek(fdopen(fd2, "rb"), 0, SEEK_SET);
    prin(fd2) ;
    close(fd2);


    return 0;
}










