/*************************************************************************
  > File Name: server.c
  > Author: One
  > Mail:838260772@qq.com 
  > Created Time: 2014年07月01日 星期二 21时12分31秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>
static void* handler(void*);
pthread_t tid;
int fd_server,fd_w;
int pid;

int main()
{
	char buf_server[32];
	fd_server=open("ser.fifo",O_RDONLY);
	printf("connect server sucess!\n");
	while(memset(buf_server,0,32),read(fd_server,buf_server,32)>0)//创建一个线程来处理
	{
		printf("server!\n");
		pthread_create(&tid,NULL,handler,buf_server);
	}
	return 0;
}

void* handler(void *buf_server)
{
	printf("get into!\n");
	fflush(stdout);
	pthread_detach(tid);

	int fd_w,i=0;
	char buf_w[32];
	char buf[1024];
	char str[32];

	char *p=buf_w;
	strcpy(buf_w,buf_server);
	while((*p>='0'&&*p<='9')||*p==' ')
		p++;

	sprintf(buf,"%s",buf_w);
	pid=atoi(buf);
	memset(buf,0,1024);
	sprintf(buf,"%d_read.fifo",pid);
	fd_w=open(buf,O_WRONLY);

	memset(str,0,32);
	while((*p++)!='\n')
		str[i++]=*p;
	str[i]='\0';

	puts(str);
	close(fd_w);
}











