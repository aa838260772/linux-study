/*************************************************************************
  > File Name: client.c
  > Author: One
  > Mail:838260772@qq.com 
  > Created Time: 2014年06月28日 星期六 00时20分25秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/time.h>
#include<unistd.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>
#include<signal.h>
#include<stdlib.h>
void handler(int num)
{
	wait();
	exit(0);
}
int main(int argc,char **argv)
{
	FILE *fp;
	int fd_server;

	int fd_r,fd_w;
	char fifo_read[32];
	char fifo_write[32];
	char buf[1024];

	sprintf(fifo_read,"%d_read.fifo",getpid());
	sprintf(fifo_write,"%d_write.fifo",getpid());
	mkfifo(fifo_read,0666);//创建管道
	mkfifo(fifo_write,0666);

	fd_server=open("ser_fifo",O_WRONLY);//连接服务器管道
	fp=fdopen(fd_server,"w");
	fprintf(fp,"%d",getpid());//向服务器发送进程pid
	fflush(fp);


	//puts(fifo_read);
	//puts(fifo_write);

	fd_r=open(fifo_read,O_RDONLY);
	fd_w=open(fifo_write,O_WRONLY);
	printf("fd_r:%d  fd_w:%d fd_server:%d\n",fd_r,fd_w,fd_server);

	close(fd_server);
	int pid;
	if((pid=fork())>0)// 父进程负责写
	{
		signal(17,handler);
		close(fd_r);
		FILE *fp_write;
		fp_write=fdopen(fd_w,"w");
		while(memset(buf,0,1024),fgets(buf,1024,stdin)!=NULL)
		{
			fprintf(fp_write,"from %d : %s",getpid(),buf);
			fflush(fp_write);
		}
		fprintf(fp_write,"bye",NULL);
		fflush(fp_write);
		close(fd_w);
		kill(pid,9);
		unlink(fifo_read);
		unlink(fifo_write);
	}
	else
	{
		close(fd_w);
		while(memset(buf,0,1024),read(fd_r,buf,1024)>0)
		{

			printf("fd_r:%d  fd_w:%d\n",fd_r,fd_w);
			write(1,buf,strlen(buf));
		}
		close(fd_r);
	}
	return 0;
}
