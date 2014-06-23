/*************************************************************************
	> File Name: my_cat.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月23日 星期一 10时19分18秒
 ************************************************************************/
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
int main(int argc,char **argv)
{
	int fd,count;
	char buf[1024];
if(argc==1)
	fd=0;
else
	fd=open(argv[1],O_RDONLY);
if(fd==-1)
{
printf("open file fail!\n");
exit(-1);
}
while(memset(buf,0,1024),(count=read(fd,buf,1024))!=0)
{
write(1,buf,count);

}
close(fd);

return 0;
}
