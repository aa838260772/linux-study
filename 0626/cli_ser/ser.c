/*************************************************************************
	> File Name: ser.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月26日 星期四 22时24分23秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<string.h>
#include<unistd.h>
int main()
{
char buf[1024];
int fd;
fd=open("fifo1",O_WRONLY);
while(memset(buf,0,1024),fgets(buf,1024,stdin)!=NULL)
{
write(fd,buf,strlen(buf));
}

close(fd);

return 0;
}
