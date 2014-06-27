/*************************************************************************
  > File Name: chat2.c
  > Author: One
  > Mail:838260772@qq.com 
  > Created Time: 2014年06月26日 星期四 20时56分13秒
 ************************************************************************/

#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<signal.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
void handler(int num)
{
wait();
exit(0);
}
int main()
{
	int fd_w,fd_r;
	char buf[1024];
	pid_t pid;
	fd_r=open("1_2.fifo",O_RDONLY);
	fd_w=open("2_1.fifo",O_WRONLY);
   printf("fd_r: %d   fd_w: %d\n",fd_r,fd_w);
	if((pid=fork())> 0)
	{//父进程负责读管道1
		close(fd_w);
		signal(17,handler);
		while(memset(buf,0,1024),read(fd_r,buf,1024)>0)
		{
			if(strncmp("bye",buf,3)==0)
				break;
			else
			{	
			write(1,buf,strlen(buf));
			fflush(fdopen(fd_r,"r"));
			}
		}
         kill(pid,2);
		close(fd_r);
//		wait();
//		while(1);
	}else
	{//子进程负责写管道2
		close(fd_r);
		FILE *fp=fdopen(fd_w,"w");
		while(memset(buf,0,1024),fgets(buf,1024,stdin)!=NULL)
		{
			fprintf(fp,"from 2: %s",buf);
			fflush(fp);
		}
		fprintf(fp,"bye",NULL);
		close(fd_w);
	}
	return 0;
}
