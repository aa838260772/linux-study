/*************************************************************************
  > File Name: chat_client.c
  > Author: One
  > Mail:838260772@qq.com 
  > Created Time: 2014年07月05日 星期六 00时20分10秒
 ************************************************************************/

#include "chat.h"
static void* pthread_handle(void*);
int main(int argc,char * argv[])
{
	if(3 != argc)
	{
		printf("EXE ip port");
		exit(-1);
	}

	int fd_client;
	if((fd_client=socket(AF_INET,SOCK_DGRAM,0)) == -1)
	{
		perror("socket!\n");
		exit(-1);
	}
	SA client_addr;
	client_addr.sin_family=AF_INET;
	client_addr.sin_port=htons(atoi(argv[2]));
	client_addr.sin_addr.s_addr=inet_addr(argv[1]);

	MSG send_msg;
	bzero(&send_msg,sizeof(MSG));
	int choice;

	send_msg.s_type=MSG_ON;//实现用户写入服务器链表
	sendto(fd_client,&send_msg,sizeof(MSG),0,(struct sockaddr*)&client_addr,sizeof(SA));

	/* while(fflush(stdin),scanf("%d",&choice)!=1 || choice<1 || choice>2)//对用户的选择作判断
	   {
	   printf("wrong choice\n");
	   printf("1.单聊模式 2.群聊模式\n:");
	   }*/
	pthread_t tid;
	pthread_create(&tid,NULL,pthread_handle,(void*)fd_client);
	printf("1.单聊模式 2.群聊模式\n:");
	
	while(1)
	{
		scanf("%d",&choice);
		if(choice==1||choice==2)
			break;
		printf("wrong choice\n");
		printf("1.单聊模式 2.群聊模式\n:");
		getchar();
		//	 fflush(stdin);
	}

    getchar();

	if(choice==1)
	{
		char ip[32]="";
		char port[16]="";

		printf(" ip  port\n:");
		scanf("%s %s",ip,port);

		send_msg.s_addr.sin_family=AF_INET;    
		send_msg.s_addr.sin_addr.s_addr=inet_addr(ip);
		send_msg.s_addr.sin_port=htons(atoi(port));
		printf("%s %d\n",ip,ntohs(send_msg.s_addr.sin_port)) ;

		send_msg.s_type=MSG_USR;
	}else
	{
		send_msg.s_type=MSG_GRP;
	}


	printf("begin!....\n");

	while(bzero(send_msg.s_msg,sizeof(send_msg.s_msg)),fgets(send_msg.s_msg,sizeof(send_msg.s_msg),stdin)!=NULL)
	{
		send_msg.s_len=strlen(send_msg.s_msg);
		sendto(fd_client,&send_msg,sizeof(MSG),0,(struct sockaddr*)&client_addr,sizeof(SA));
	}
	send_msg.s_type=MSG_OFF;
	sendto(fd_client,&send_msg,sizeof(MSG),0,(struct sockaddr*)&client_addr,sizeof(SA));
	close(fd_client);
	return 0;
}

void* pthread_handle(void* arg)
{//服务器转发的时候没有发送MSG结构体
	pthread_detach(pthread_self());
	int fd_client=(int)arg;
	MSG recv_msg;
	char buf[1024];
	SA client_addr;
	int addr_len=sizeof(SA);
	//while(bzero(recv_msg.s_msg,sizeof(recv_msg.s_msg)),recvfrom(fd_client,&recv_msg,sizeof(recv_msg.s_msg),0,(struct sockaddr*)&client_addr,addr_len))
	while(bzero(buf,1024),recvfrom(fd_client,buf,1024,0,NULL,NULL))
	{
		printf("%s",buf);
	}
}
