/*************************************************************************
  > File Name: chat_client.c
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
#include <pthread.h>
void* recv_func(void* arg);
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

	int chat_port=htons(atoi(argv[2]));
	char chat_ip[32]="";
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

	int ip[4];
	char chat_msg[1024];
	while(printf("who(ip):"),fflush(stdout),bzero(chat_ip,32),fgets(chat_ip,32,stdin)!=NULL)
	{
		if(chat_ip[0] == '\n')
		{
			continue;
		}else
		{
			if(4 != sscanf(chat_ip,"%d.%d.%d.%d",ip,ip+1,ip+2,ip+3))
			{
				printf("wrong format!\n");
				continue;
			}else if(ip[0]> 255 || ip[1] > 255 || ip[2] > 255 || ip[3] > 255)
			{
				printf("wrong ip!\n");
				continue;
			}else
			{
				chat_ip[strlen(chat_ip)-1] = '\0';
				bzero(chat_msg,1024);
				client_addr.sin_family=AF_INET;
				client_addr.sin_port=chat_port;
				client_addr.sin_addr.s_addr=inet_addr(chat_ip);
				pthread_t tid;
				pthread_create(&tid,NULL,recv_func,(void*)&fd_server);
				while(bzero(chat_msg,1024),fgets(chat_msg,1024,stdin)!=NULL)
				{
					//puts(chat_msg);
					int t;
					t=sendto(fd_server,chat_msg,strlen(chat_msg),0,(struct sockaddr*)&client_addr,sizeof(client_addr));
					printf("t:%d\n",t);
				}
				sendto(fd_server,"bye",strlen("bye"),0,(struct sockaddr*)&client_addr,sizeof(client_addr));
			}
		}
	}
	return 0;
}

void* recv_func(void *arg)
{
	pthread_detach(pthread_self());
	//int fd_server=(int)arg;
	int fd_server=*(int *)arg;
	struct sockaddr_in client_addr;
	int len=sizeof(client_addr);
	char chat_msg[1024]="";
	while(bzero(chat_msg,1024),recvfrom(fd_server,chat_msg,1024,0,(struct sockaddr*)&client_addr,&len))
	{
		if(strcmp(chat_msg,"bye") !=0 )
			printf("%s %d\n %s",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port),chat_msg);
		else
			break;
	}
}









