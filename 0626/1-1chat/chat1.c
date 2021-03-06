/*************************************************************************
  > File Name: chat1.c
  > Author: One
  > Mail:838260772@qq.com 
  > Created Time: 2014年06月26日 星期四 20时49分15秒
 ************************************************************************/

#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>
void handle(int num)
{
wait();
exit(0);
}
int main()
{
	int fd_w,fd_r;
	char buf[1024];
	pid_t pid;
	fd_w=open("1_2.fifo",O_WRONLY);//双方打开两个管道的顺序应该一样，
	fd_r=open("2_1.fifo",O_RDONLY);
  printf("fd_r: %d   fd_w : %d\n",fd_r,fd_w);
	if((pid=fork())>0)
	{//父进程负责写管道1
		close(fd_r);
		FILE *fp=fdopen(fd_w,"w");
		signal(17,handle);//注册17号信号量，子进程结束后发来17号信号量，
		while(memset(buf,0,1024),fgets(buf,1024,stdin)!=NULL)
		{
			fprintf(fp,"from 1: %s",buf);
			fflush(fp);
		}
		close(fd_w);
        kill(pid,2);
        fprintf(fp,"bye",NULL);
//		while(1);
	}else
	{//子进程读管道2
		close(fd_w);
		while(memset(buf,0,1024),read(fd_r,buf,1024)>0)
		{
			if(strncmp("bye",buf,3)!=0)
			write(1,buf,strlen(buf));
			else
				break;
		}
		close(fd_r);
	}
	return 0;
}
