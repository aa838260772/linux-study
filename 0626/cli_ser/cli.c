/*************************************************************************
	> File Name: cli.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月26日 星期四 22时19分54秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<string.h>
#include<unistd.h>
int main()
{
int fd;
fd=open("fifo1",O_RDONLY);
char buf[1024];
while(memset(buf,0,1024),read(fd,buf,1024)>0)
{
write(1,buf,strlen(buf));
}
close(fd);
return 0;
}
