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
	if(argc != 4)
	{
		printf("EXE IP PORT");
		exit(-1);
	}

	int fd_server ,fd_client;
	fd_server = listen_socket(argv[1] ,argv[2]);

	SA server_addr,client_addr;
	int addr_len = sizeof(SA);

	int cnt =atoi(argv[3]);
	PCHLD childs =(PCHLD)calloc(cnt,sizeof(CHLD));
	int fd_max = make_child(childs,cnt);
	int index;
    fd_set fd_read ,fd_ready;
    FD_ZERO(&fd_read);
	for(index =0 ;index <cnt ; index ++)
	{
    FD_SET(childs[index].s_fd_wr ,&fd_read);
	}

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
		for( index = 0; index <cnt ; ++index)
		{
			if(childs[index].s_status == S_IDLE)
				break;
		}
		if(index != cnt)
		{
			childs[index].s_status = S_BUSY;
		 send_fd(childs[index].s_fd_wr ,fd_client);
		}
       
	    fd_ready =fd_read;	  
		select(fd_max+1 ,&fd_ready,NULL,NULL,NULL);
		for(index =0 ;index <cnt ;index ++)
		{
			char ch;
			if(FD_ISSET(childs[index].s_fd_wr,&fd_ready))
		{
			printf("a process idle\n");
         read(childs[index].s_fd_wr,&ch,1);
		 childs[index].s_status = S_IDLE;
			}
		}
	}
	return 0;
}


