/*************************************************************************
  > File Name: chat2.c
  > Author: One
  > Mail:838260772@qq.com 
  > Created Time: 2014年06月26日 星期四 20时56分13秒
 ************************************************************************/

#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int fd_w,fd_r;
	char buf[1024];
	fd_r=open("1_2.fifo",O_RDONLY);
	fd_w=open("2_1.fifo",O_WRONLY);
   printf("fd_r: %d   fd_w: %d\n",fd_r,fd_w);
	if(fork()>0)
	{//父进程负责读管道1
		close(fd_w);
		while(memset(buf,0,1024),read(fd_r,buf,1024)>0)
		{
			write(1,buf,strlen(buf));
			fflush(fdopen(fd_r,"r"));
		}
		close(fd_r);
		wait();
	}else
	{//子进程负责写管道2
		close(fd_r);
		FILE *fp=fdopen(fd_w,"w");
		while(memset(buf,0,1024),fgets(buf,1024,stdin)!=NULL)
		{
			fprintf(fp,"from 2: %s",buf);
			fflush(fp);
		}
		close(fd_w);
	}
	return 0;
}
