/*************************************************************************
  > File Name: chat_server.c
  > Author: One
  > Mail:838260772@qq.com 
  > Created Time: 2014年07月04日 星期五 21时56分21秒
 ************************************************************************/

#include "chat.h"
static void msg_on(int , pNode*, SA*);
static void msg_off(pNode*, SA*);
static void msg_grp(int , MSG , pNode,SA);
static void msg_usr(int , MSG , SA);

int main(int argc,char * argv[])
{
	if(3 !=argc)
	{
		printf("EXE IP PORT!\n");
		exit(-1);
	}

	int fd_server;
	if(-1 == (fd_server=socket(AF_INET,SOCK_DGRAM,0)))//分配套接口
	{
		perror("socket!\n");
		exit(-1);
	}

	SA server_addr,client_addr;
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(atoi(argv[2]));
	server_addr.sin_addr.s_addr=inet_addr(argv[1]);

	if(-1 == bind(fd_server,(struct sockaddr*)&server_addr,sizeof(server_addr)))//本地地址与套接口捆绑
	{
		perror("error!\n");
		exit(-1);
	}
	/*----------------前面的东西都是一样的------*/
	pNode head=NULL;//存储客户端信息的链表头结点,初始为空

	fd_set fd_read,fd_ready;//使用select轮询前的准备
	FD_ZERO(&fd_read);
	FD_SET(fd_server,&fd_read);

	MSG recv_msg;
	int addr_len=sizeof(SA);
	while(1)
	{
		fd_ready=fd_read;
		struct timeval tm;
		tm.tv_sec=0;
		tm.tv_usec=1000;

		bzero(&recv_msg,sizeof(MSG));
		bzero(&client_addr,sizeof(SA));

		select(fd_server+1,&fd_ready,NULL,NULL,&tm);

		if(FD_ISSET(fd_server,&fd_ready))
		{
			recvfrom(fd_server,&recv_msg,sizeof(MSG),0,(struct sockaddr*)&client_addr,&addr_len);
			//printf("s_type:%d\n",recv_msg.s_type);
			switch(recv_msg.s_type)
			{
				case MSG_USR:
					msg_usr(fd_server,recv_msg,client_addr);
					break;
				case MSG_GRP:
					msg_grp(fd_server,recv_msg,head,client_addr);
					break;
				case MSG_ON:
					msg_on(fd_server,&head,&client_addr);
					break;
				case MSG_OFF:
					msg_off(&head,&client_addr);
					break;
				default:
					break;
			}
		}
	}
	return 0;	
}

void msg_on(int fd_server,pNode *head,SA *client_addr)//链表头插法
{
     char buf[MSG_LEN];
	pNode p=(pNode)malloc(sizeof(Node));
	p->s_addr=*client_addr;
	p->s_next=*head;
	*head=p;
	printf("%s %d is on!\n",inet_ntoa(client_addr->sin_addr),ntohs(client_addr->sin_port));
pNode q=*head;
while(q)
{
	sprintf(buf,"%s %d is on!\n",inet_ntoa(q->s_addr.sin_addr),ntohs(q->s_addr.sin_port));
	sendto(fd_server , buf ,strlen(buf), 0 , (struct sockaddr*)client_addr,sizeof(SA));
	q=q->s_next;
}

}

void msg_off(pNode *head,SA *client_addr)//删除地址结构体为client_addr结构体,传递指针的时候效率比较高
{
	pNode pCur,pPre;
	pPre=NULL;
	pCur=*head;
	while(pCur)
	{
		if((pCur->s_addr).sin_port==client_addr->sin_port && (pCur->s_addr).sin_addr.s_addr==client_addr->sin_addr.s_addr)//找到了直接退出循环 
		{
			break;
		}else
		{
			pPre=pCur;
			pCur=pCur->s_next;
		}
	}
	if(pCur == NULL)
	{
		printf("not exist!\n");
	}else
	{
		if(pPre==NULL)
		{
			*head=(*head)->s_next;
		}else
		{
			pPre->s_next=pCur->s_next;
		}
		free(pCur);
		printf("%s %d is off!\n",inet_ntoa(client_addr->sin_addr),ntohs(client_addr->sin_port));
	}
}

void msg_grp(int fd_server,MSG recv_msg,pNode head,SA client_addr)
{

	char buf[MSG_LEN]="";
	while(head)
	{
		//printf("%d     %d\n",head->s_addr.sin_addr.s_addr,client_addr.sin_addr.s_addr);

		//if(strcmp(inet_ntoa(head->s_addr.sin_addr),inet_ntoa(client_addr.sin_addr)) != 0 || head->s_addr.sin_port != client_addr.sin_port)

		bzero(buf,MSG_LEN);
		sprintf(buf,"%s %d :%s",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port),recv_msg.s_msg);
		
		if(head->s_addr.sin_addr.s_addr != client_addr.sin_addr.s_addr || head->s_addr.sin_port != client_addr.sin_port)//端口和ip相同的不发送
			sendto(fd_server,buf,MSG_LEN,0,(struct sockaddr*)&(head->s_addr),sizeof(SA));
		head=head->s_next;
	}
}

void msg_usr(int fd_server,MSG recv_msg,SA client_addr)
{
//	printf("%s     %d\n",inet_ntoa(recv_msg.s_addr.sin_addr),ntohs(recv_msg.s_addr.sin_port));

	char buf[MSG_LEN]="";
	sprintf(buf,"%s %d :%s",inet_ntoa(client_addr.sin_addr),client_addr.sin_port,recv_msg.s_msg);
	sendto(fd_server,buf,MSG_LEN,0,(struct sockaddr*)&(recv_msg.s_addr),sizeof(SA));
}
