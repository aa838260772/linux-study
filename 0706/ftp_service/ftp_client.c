/*************************************************************************
  > File Name: ftp_client.c
  > Author: One
  > Mail:838260772@qq.com 
  > Created Time: 2014年07月07日 星期一 00时49分47秒
 ************************************************************************/

#include "process.h"
int main(int argc,char **argv)
{

	if(argc != 3)
	{
		printf("EXE IP PORT");
		exit(-1);
	}

	int fd_client;
	fd_client = socket(AF_INET ,SOCK_STREAM ,0);
	if(fd_client == -1)
	{
		perror("socket\n");
		exit(-1);
	}

	SA server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	server_addr.sin_port = htons(atoi(argv[2]));

	if(-1 == connect(fd_client,(const struct  sockaddr*)&server_addr,sizeof(SA)))
	{
		perror("connect");
		close(fd_client);
		exit(-1);
	}

	MSG send_msg,recv_msg;
	int read_n;
	printf("[syswj@~]:");
	while(bzero(&send_msg,MSG_LEN+4) ,fgets(send_msg.s_msg,MSG_LEN,stdin)!=0)
	{
		char buf1[32]="";
		char buf2[32]="";
		sscanf(send_msg.s_msg,"%s %s",buf1,buf2);
		send_msg.s_len = strlen(send_msg.s_msg);
		send(fd_client ,&send_msg,send_msg.s_len+4,0);
		if(strcmp(buf1,"puts") == 0)
		{   double  i=0;
			int fd_r = open(buf2 ,O_RDONLY);
			while(bzero(&send_msg ,sizeof(MSG)) ,read(fd_r , send_msg.s_msg ,sizeof(MSG))>0 )
			{
				puts(send_msg.s_msg);
				send_msg.s_len = strlen(send_msg.s_msg);
				send(fd_client , &send_msg ,send_msg.s_len+4,0);
				i += send_msg.s_len;
			}
			sprintf(send_msg.s_msg,"over");
			send_msg.s_len = strlen(send_msg.s_msg);
			send(fd_client ,&send_msg ,send_msg.s_len+4,0);
			printf("upload %.2fkb\n",i/1024);
		}

		while(bzero(&recv_msg,sizeof(MSG)) ,recv(fd_client ,&recv_msg,4,0)>0)
		{
			recv(fd_client , recv_msg.s_msg ,recv_msg.s_len,0);
			if(strcmp(recv_msg.s_msg ,"over")== 0 )
				break;
			if(strcmp(buf1,"gets") == 0)
			{
				int fd_w =open(buf2 ,O_WRONLY|O_CREAT ,0666);
				write(fd_w ,&recv_msg.s_msg ,recv_msg.s_len+4);
			}else
			{
				printf("%s",recv_msg.s_msg);
			}
			fflush(stdout);
		}
	printf("[syswj@~]:");
	}
	strcpy(send_msg.s_msg , "bye");
	send_msg.s_len = strlen(send_msg.s_msg);
	send(fd_client , &send_msg ,send_msg.s_len+4,0);
	return 0;
}








