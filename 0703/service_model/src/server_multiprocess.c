/*************************************************************************
  > File Name: server_multiprocess.c
  > Author: One
  > Mail:838260772@qq.com 
  > Created Time: 2014年07月03日 星期四 10时03分25秒
 ************************************************************************/

#include "msg.h"
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
	int pid;
	while(fd_client=accept(fd_server,(struct sockaddr*)&client_addr,&addr_len))
	{
		if(fd_client == -1)
		{
			if(errno == EINTR)
			{
				continue;
			}
		}
		printf("a client connect :%s:%d\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
		if(fork() == 0)
		{
			close(fd_server);
			handle_request(fd_client);
			exit(0);
		}
	}
	return 0;
}


