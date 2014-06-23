/*************************************************************************
	> File Name: my_mv.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月23日 星期一 14时19分15秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
int main(int argc,char **argv)
{
//假设传的第二个参数也是文件名
int fd_src,fd_des;
char buf[1024];
char str[1024];
ssize_t count;
int df;
memset(str,0,1024);
struct stat mystat;
fd_src=open(argv[1],O_RDONLY);
stat(argv[2],&mystat);
if(!S_ISDIR(mystat.st_mode))
   fd_des=open(argv[2],O_WRONLY|O_CREAT,0666 );
else
{
sprintf(str,"%s%s",argv[2],argv[1]);
fd_des=open(str,O_WRONLY|O_CREAT,0666);
}
if(fd_src==-1||fd_des==-1)
{
printf("open file error!\n");
exit(-1);
}
while(memset(buf,0,1024),(count=read(fd_src,buf,1024))>0)
{
 write(fd_des,buf,count);
}
close(fd_src);
close(fd_des);
df=unlink(argv[1]);
if(df==-1)
	printf("delete failed!\n");
return 0;
}
