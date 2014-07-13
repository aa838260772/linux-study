/*************************************************************************
  > File Name: server.c
  > Author: One
  > Mail:838260772@qq.com 
  > Created Time: 2014年07月02日 星期三 15时54分34秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<arpa/inet.h>
#define IP "192.168.1.138"
#define PORT 8888
int main()
{
	int fd_server,fd_client;
	fd_server=socket(AF_INET,SOCK_STREAM,0);
	if(fd_server==-1)
	{
		perror("socket");
		exit(-1);
	}
	//绑定bind
	struct sockaddr_in server_addr;
	memset(&server_addr,0,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(PORT);//本机字节转化成网络字节，小端转化大端
	server_addr.sin_addr.s_addr=inet_addr(IP);//字符串转化成网络字节序
	if(bind(fd_server,(const struct sockaddr*)&server_addr,sizeof(server_addr))==-1)
	{//地址格式的转换
		perror("bind");
		close(fd_server);
		exit(-1);
	}
	//监听
	if(listen(fd_server,6)==-1)
	{
		perror("listen");
		close(fd_server);
		exit(-1);
	}
	//连接accept
	struct sockaddr_in client_addr;
	int len=sizeof(client_addr);
	while(1)
	{
		fd_client= accept(fd_server,(struct sockaddr*)&client_addr,&len);
		char recv_buf[1024]="";
		int  recv_n=recv(fd_client,recv_buf,1024,0);//用read也一样
		printf("recv from IP:%s\nMsg:%s\nLen:%d\n ",inet_ntoa(client_addr.sin_addr),recv_buf,recv_n);
		// int send_n=send(fd_client,recv_buf,recv_n,0);
		int fd_r;//要对末尾的\n处理
		int i=0;
		while(recv_buf[i]!='\n')
			i++;
		recv_buf[i]='\0';

		fd_r=open(recv_buf,O_RDONLY);
		// printf("send to IP:%s\nMsg:%s\nLen:%d\n ",inet_ntoa(client_addr.sin_addr),recv_buf,send_n);
		//关闭
		puts(recv_buf);
		while(memset(recv_buf,0,1024),read(fd_r,recv_buf,1024)>0)
		{
			send(fd_client,recv_buf,strlen(recv_buf),0);
		}
		printf("copy over!\n");
	}
	close(fd_server);
	close(fd_client);
	return 0;
}
