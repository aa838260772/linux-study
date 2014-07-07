/*************************************************************************
  > File Name: ftp_server.c
  > Author: One
  > Mail:838260772@qq.com 
  > Created Time: 2014年07月07日 星期一 01时02分03秒
 ************************************************************************/

#include "process.h"
#include <errno.h>
int main(int argc ,char **argv)
{
	if(argc != 3)
	{
		printf("EXE IP PORT");
		exit(-1);
	}

	int fd_server ,fd_client;
	fd_server = listen_socket(argv[1] ,argv[2]);

	SA server_addr,client_addr;
	int addr_len = sizeof(SA);
	while(fd_client = accept(fd_server ,(struct sockaddr*)&client_addr ,&addr_len) )
	{
		if(fd_client == -1)
		{
			if(errno == EINTR)
			{
				continue;
			}
		}
			printf("%s %d online\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
         if(fork() == 0)
		 {
		 close(fd_server);
		 handle_request(fd_client);
         exit(0);//子进程执行完退出
		 }
	}
	return 0;
}


