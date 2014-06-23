/*************************************************************************
	> File Name: my_dup.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月23日 星期一 15时27分22秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
int main(int argc,char **argv)
{
int fd_wr;
char buf[1024];
int count;
fd_wr=open(argv[1],O_WRONLY|O_CREAT,0666);
//while(fflush(stdin),(count=read(0,buf,1024))>0)
//{
//write(fd_wr,buf,count);
dup2(fd_wr,1);
write(1,buf,count);
//}
printf("hello1");
close(fd_wr);
printf("hello2");
return 0;
}
