/*************************************************************************
	> File Name: my_select.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月24日 星期二 19时38分46秒
 ************************************************************************/

#include <stdio.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
int main()
{
int fd1,fd2;
struct timeval tm;
char buf[1024];
fd1=open("a.txt",O_RDONLY|O_CREAT);
fd2=open("b.txt",O_RDONLY|O_CREAT);
fd_set fd_rd,fd_ready;

FD_ZERO(&fd_rd);
FD_ZERO(&fd_ready);

//FD_SET(0,&fd_rd);
//FD_SET(fd1,&fd_rd);
//FD_SET(fd2,&fd_rd);

int max = fd1>fd2?fd1:fd2;

while(1)
{
 tm.tv_sec=3;
 tm.tv_usec=0;
 //fd_ready=fd_rd;

FD_SET(0,&fd_ready);
FD_SET(fd1,&fd_ready);
FD_SET(fd2,&fd_ready);

//printf("%d  \n",select(max+1,&fd_ready,NULL,NULL,&tm));
if(select(max+1,&fd_ready,NULL,NULL,NULL)==-1)
{
perror("select");
break;
}
if(FD_ISSET(0,&fd_ready))
{
memset(buf,0,sizeof(buf));
read(0,buf,sizeof(buf)-1);
write(1,buf,strlen(buf));
}

if(FD_ISSET(fd1,&fd_ready))
{
memset(buf,0,sizeof(buf));
read(fd1,buf,sizeof(buf)-1);
write(1,buf,strlen(buf));
}

if(FD_ISSET(fd2,&fd_ready))
{
memset(buf,0,sizeof(buf));
read(fd2,buf,sizeof(buf)-1);
//puts(buf);不要用puts，会自带回车！！！
write(1,buf,strlen(buf));
}
}

close(fd1);
close(fd2);
return 0;
}
