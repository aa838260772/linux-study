/*************************************************************************
  > File Name: client.c
  > Author: One
  > Mail:838260772@qq.com 
  > Created Time: 2014年07月02日 星期三 19时09分55秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#define IP "192.168.1.100"
#define PORT 6688
int main()
{
	struct sockaddr_in server_addr,client_addr;
	int fd_client;
	if((fd_client=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("socket\n");
		exit(-1);
	}

	memset(&client_addr,0,sizeof(client_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(PORT);
	server_addr.sin_addr.s_addr=inet_addr(IP);
	if((connect(fd_client,(struct sockaddr*)&server_addr,sizeof(server_addr)))==-1)
	{
		perror("connect!\n");
		close(fd_client);
		exit(-1);
	}
	printf("connecting!\n");

	char p[32]="";
	char buf[1024];
	int fd_w;
	fd_w=open("a.mv",O_WRONLY|O_CREAT,0666);
	while(1)
	{
		fgets(p,32,stdin);
		send(fd_client,p,strlen(p),0);
		while(memset(buf,0,1024),read(fd_client,buf,1024)>0)
		{
			write(fd_w,buf,sizeof(buf));
		}
		printf("success!\n");
		fflush(stdout);

		//此处有问题，read读socket的内容时是阻塞函数，会阻塞的，要把消息封装成MSG结构体，先读长度，长度大于0在读内容，否则表示读完，退出内部的while
	}
	close(fd_w);
	close(fd_client);
	return 0;
}
