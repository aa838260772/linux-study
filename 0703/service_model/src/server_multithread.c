/*************************************************************************
  > File Name: server_multithread.c
  > Author: One
  > Mail:838260772@qq.com 
  > Created Time: 2014年07月03日 星期四 10时03分25秒
 ************************************************************************/

#include "msg.h"
#include <pthread.h>
static void* thread_handle(void*);
int main(int argc,char * argv[])
{
 signal(13,SIG_IGN);
	if(argc!=3)
	{
		printf("argu not enough\n");
		exit(-1);
	}
	int fd_server,fd_client,fd_file;
	struct sockaddr_in server_addr,client_addr;
	int addr_len=sizeof(client_addr);
	fd_server=listen_fd(argv[1],argv[2]);
	while(fd_client=accept(fd_server,(struct sockaddr*)&client_addr,&addr_len))
	{
		printf("a client connect :%s:%d\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
     pthread_t tid;
	pthread_create(&tid,NULL,thread_handle,(void*)&fd_client);
	}
return 0;
}

void* thread_handle(void* arg) 
{
int fd_client=*(int*)arg;
pthread_detach(pthread_self());
handle_request(fd_client);
}
