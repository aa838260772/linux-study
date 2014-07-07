/*************************************************************************
  > File Name: ../src/msg.c
  > Author: One
  > Mail:838260772@qq.com 
  > Created Time: 2014年07月03日 星期四 16时13分23秒
 ************************************************************************/

#include "msg.h"
int listen_fd(char *ip,char *port)
{
	int fd_server;
	int reuse=1;
	struct sockaddr_in server_addr;
	if((fd_server=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("sock\n");
		exit(-1);
	}
	if(0!=setsockopt(fd_server,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int)))
	{
		perror("setsockopt");
		close(fd_server);
		exit(-1);
	}
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr(ip);
	server_addr.sin_port=htons(atoi(port));
	if(-1==bind(fd_server,(struct sockaddr*)&server_addr,sizeof(server_addr)))
	{
		perror("bind");
		close(fd_server);
		exit(-1);
	}
	if(-1==listen(fd_server,5))
	{
		perror("listen");
		close(fd_server);
		exit(-1);
	}
return fd_server;
}

void handle_request(int fd_client)
{
     	MSG msg,send_msg;
        int read_n;
		int fd_file;
		memset(&msg,0,sizeof(msg));
		recv(fd_client,&msg,MSG_LEN,0);//先收长度，再收数据
		recv(fd_client,msg.s_buf,msg.s_len,0);
		printf("recv msg %s\n",msg.s_buf);
		fd_file=open(msg.s_buf,O_RDONLY);
		while(memset(&send_msg,0,sizeof(msg)),(read_n=read(fd_file,send_msg.s_buf,MSG_SIZE))>0)
		{
			send_msg.s_len=read_n;
			send(fd_client,&send_msg,read_n+MSG_LEN,0);
		}
		send_msg.s_len=0;
		send(fd_client,&send_msg,read_n+MSG_LEN,0);
		close(fd_file);
		close(fd_client);
}
















