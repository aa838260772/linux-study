/*************************************************************************
  > File Name: client.c
  > Author: One
  > Mail:838260772@qq.com 
  > Created Time: 2014年07月04日 星期五 09时39分11秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>

int main(int argc, char **argv)
{
	if(argc !=3)
	{
		printf("usage:exe ip port");
		exit(-1);
	}
	int fd_server;
	char buf[1024];
	fd_server = socket(AF_INET , SOCK_DGRAM,0);
	if(fd_server == -1)
	{
		perror("socket");
		exit(-1);
	}
	struct sockaddr_in server_addr,client_addr;
	int len =sizeof(client_addr);
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(atoi(argv[2]));
	server_addr.sin_addr.s_addr=inet_addr(argv[1]);
	if(-1 == bind(fd_server,(struct sockaddr*)&server_addr,sizeof((server_addr))))
	{
		perror("bind");
		exit(-1);
	}
  while(1)
  {
  bzero(&client_addr,len);
  bzero(buf,1024);
  recvfrom(fd_server,buf,1024,0,(struct sockaddr*)&client_addr,&len);
  printf("ip:port :%s  %d %s\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port),buf);
  sendto(fd_server,buf,strlen(buf),0,(struct sockaddr*)&client_addr,sizeof(client_addr));
  }
	return 0;
}









