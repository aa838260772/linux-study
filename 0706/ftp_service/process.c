/*************************************************************************
  > File Name: process.c
  > Author: One
  > Mail:838260772@qq.com 
  > Created Time: 2014年07月06日 星期日 20时12分31秒
 ************************************************************************/

#include "process.h"
#include <dirent.h>
static void  my_cd(int,char*);
static void command_process(int ,MSG);
static void my_ls(int);
static void my_ll(int);
static void download(int,char*);
static void upload(int,char*);
static void rm(int ,char*);
int listen_socket(char *argv1,char* argv2)
{
	int fd_server;

	fd_server=socket(AF_INET , SOCK_STREAM , 0);//绑定一个socket
	if(fd_server == -1)
	{
		perror("socket!\n");
		exit(-1);
	}

	SA server_addr,client_addr;
	server_addr.sin_family = AF_INET;//指定ip 端口号以及协议
	server_addr.sin_addr.s_addr = inet_addr(argv1);
	server_addr.sin_port = htons(atoi(argv2));

	if(-1 == bind(fd_server ,(const struct sockaddr*)&server_addr ,sizeof(SA)))
	{//绑定socket
		perror("bind\n");
		close(fd_server);
		exit(-1);
	}

	if(-1 == listen(fd_server ,5))//排队连接的队列最长为5
	{
		perror("listen\n");
		close(fd_server);
		exit(-1);
	}
	return fd_server;
}

void handle_request(int fd_client)
{

	int read_n;
	int  i;
    MSG send_msg,recv_msg; 

	while(bzero(&recv_msg,sizeof(MSG)) ,(read_n =  recv(fd_client,&recv_msg,4 ,0)) > 0)
	{
		recv(fd_client ,recv_msg.s_msg ,recv_msg.s_len ,0);
		if(strcmp(recv_msg.s_msg ,"bye")==0)
		{
			break;
		}
		i=0;
		while(recv_msg.s_msg[i]!='\n')
		{
			i++;
		}
		recv_msg.s_msg[i] = '\0';
		fflush(stdout);
		command_process(fd_client ,recv_msg);//命令处理函数
	}
	printf("off\n");
	close(fd_client);
}


void my_cd(int fd_client,char *path)
{
	int res;
	res = chdir(path);
	if(res == -1)
	{
	MSG send_msg;
    sprintf(send_msg.s_msg,"unvaluable path",NULL);
	send_msg.s_len = strlen(send_msg.s_msg);
	send(fd_client ,&send_msg ,send_msg.s_len+4 ,0);
	}
}

void command_process(int fd_client ,MSG recv_msg)
{
	char buf1[20]="";
	char buf2[20]="";
	sscanf(recv_msg.s_msg,"%s %s",buf1,buf2);
	if(strcmp(buf1,"cd") == 0)
	{
		my_cd(fd_client ,buf2);
	}
	else if(strcmp("ls", buf1) == 0)
	{
		if(strcmp(buf2 , "")==0)
			my_ls(fd_client);
		else if(strcmp(buf2 ,"-al") == 0)
			my_ll(fd_client);
	}
	else if(strcmp(buf1 ,"gets")==0)
	{
		download(fd_client ,buf2);
		}
    else if(strcmp(buf1 ,"puts")==0)
        {
		upload(fd_client , buf2);
		}
    else if(strcmp(buf1 ,"rm")==0)
	{
	rm(fd_client ,buf2);
	}

    MSG send_msg;
	bzero(&send_msg , sizeof(MSG));
	sprintf(send_msg.s_msg,"%s","over");
	send_msg.s_len = strlen(send_msg.s_msg);
	send(fd_client,&send_msg,send_msg.s_len+4,0);
}

void my_ls(int fd_client)
{
	DIR *dir;
	struct dirent *mydir;
	MSG send_msg;
	if((dir = opendir("./")) == NULL)
	{
		printf("open dir failed!\n");
		exit(-1);
	}
	while(bzero(&send_msg ,sizeof(MSG)),(mydir = readdir(dir)) !=NULL)
	{
        sprintf(send_msg.s_msg ,"%s  ",mydir->d_name);
		send_msg.s_len = strlen(send_msg.s_msg);
		send(fd_client,&send_msg,send_msg.s_len+4,0);
    }
	strcpy(send_msg.s_msg,"\n");
	send_msg.s_len = strlen(send_msg.s_msg);
   send(fd_client ,&send_msg,send_msg.s_len+4,0);
}

void my_ll(int fd_client)
{
	DIR *dir;
	struct dirent *mydir;
	MSG send_msg;
	if((dir = opendir("./")) == NULL)
	{
		printf("open dir failed!\n");
		exit(-1);
	}
	while(bzero(&send_msg ,sizeof(MSG)),(mydir = readdir(dir)) !=NULL)
	{
		sprintf(send_msg.s_msg,"%d  %d  %d  %c  %s\n",mydir->d_reclen ,mydir->d_off ,mydir->d_ino ,mydir->d_type ,mydir->d_name);
       send_msg.s_len = strlen(send_msg.s_msg);
		send(fd_client , &send_msg ,send_msg.s_len+4 ,0);
	}
}

void upload(int fd_client ,char *buf2)
{
	MSG recv_msg;
	int fd_w = open(buf2 ,O_WRONLY|O_CREAT ,0666);
	printf("begin upload!\n");
	while(bzero(&recv_msg ,sizeof(MSG)) ,recv(fd_client ,&recv_msg ,4 ,0)>0)
	{
		recv(fd_client ,recv_msg.s_msg ,recv_msg.s_len , 0);
		 if(strcmp(recv_msg.s_msg ,"over") == 0)
			 break;
		write(fd_w ,recv_msg.s_msg ,recv_msg.s_len);
	}
	printf("end upload!\n");
}

void download(int fd_client ,char *buf2)
{
	MSG send_msg;
    int fd_r = open(buf2 ,O_RDONLY);
    double i=0;
	printf("begin download!\n");
	while(bzero(&send_msg ,sizeof(MSG)) ,read(fd_r , send_msg.s_msg ,sizeof(MSG))>0 )
			{
				send_msg.s_len = strlen(send_msg.s_msg);
				send(fd_client , &send_msg ,send_msg.s_len+4,0);
				i=i+send_msg.s_len;
			}
			sprintf(send_msg.s_msg,"over");
			send_msg.s_len = strlen(send_msg.s_msg);
			send(fd_client ,&send_msg ,send_msg.s_len+4,0);
			printf("download  %.2fkb\n",i/1024);
}

void rm(int fd_client ,char *buf2)
{
	int res;
	res = unlink(buf2);
	if(res == -1)
	{
	MSG send_msg;
    sprintf(send_msg.s_msg,"file not exit",NULL);
	send_msg.s_len = strlen(send_msg.s_msg);
	send(fd_client ,&send_msg ,send_msg.s_len+4 ,0);
	}
}





