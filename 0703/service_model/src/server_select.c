/*************************************************************************
  > File Name: server_select.c
  > Author: One
  > Mail:838260772@qq.com 
  > Created Time: 2014年07月03日 星期四 10时03分25秒
 ************************************************************************/

#include "msg.h"
#include <pthread.h>
#include<errno.h>
void handler()
{
	while(waitpid(-1,NULL,WNOHANG)>0);
}
int main(int argc,char * argv[])
{
	signal(13,SIG_IGN);
	signal(17,handler);
	if(argc!=3)
	{
		printf("argu not enough\n");
		exit(-1);
	}
	int fd_server,fd_client,fd_file;
	struct sockaddr_in server_addr,client_addr;
	int addr_len=sizeof(client_addr);
	fd_server=listen_fd(argv[1],argv[2]);

	fd_set fd_read,fd_ready;
	FD_ZERO(&fd_read);
	FD_SET(fd_server,&fd_read);

	while(1)
	{
		fd_ready=fd_read;
		select(fd_server+1,&fd_ready,NULL,NULL,NULL);
		if(FD_ISSET(fd_server,&fd_ready))
		{
			fd_client = accept(fd_server,(struct sockaddr*)&client_addr,&addr_len);
			printf("a client connect :%s:%d\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
			handle_request(fd_client);
		}
	}
	return 0;
}


