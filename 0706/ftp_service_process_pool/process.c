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
static void child_main(int);
int  make_child(PCHLD arr , int cnt)//创建进程池，并记录子进程列表中去
{
	printf("make_child\n");
	pid_t pid;
	int index;
	int fd_max = 0x80000000;
	for(index = 0 ;index < cnt ; index ++)
	{
		int fds[2];
		socketpair(AF_LOCAL ,SOCK_STREAM ,0 ,fds);
		pid =fork();
		if(pid == 0)
		{
			close(fds[0]);
			child_main(fds[1]);//把子进程的文件描述符也传递过去

		}else
		{
			close(fds[1]);
			arr[index].s_fd_wr = fds[0];
			arr[index].s_status = S_IDLE;
			arr[index].s_pid = pid;
			if(fds[0] > fd_max)
				fd_max = fds[0];
		}
	}
	return fd_max;
}

void child_main(int fds)//子进程处理函数
{
	printf("child_main\n");
	int fd_client;
	while(1)
	{
		recv_fd(fds,&fd_client);
		printf("a process busy\n");
		handle_request(fd_client);//recv_fd收到父进程传来的fd_clien后处理
		printf("%d\n",fd_client);
		write(fds ,"1",1);
	}
}

void send_fd(int sockfd,int fd_to_send)//发送文件描述符
{
	struct msghdr send_msg;
	struct cmsghdr* pcmsg;

	int cmsglen = CMSG_LEN(sizeof(int));
	pcmsg = (struct cmsghdr*)calloc(1,cmsglen);
	bzero(&send_msg ,sizeof(send_msg));

	send_msg.msg_name = NULL;
	send_msg.msg_namelen = 0;
	send_msg.msg_flags = 0;

	char buf[32]="hello world\n";
	struct iovec bufs[1];
	bufs[0].iov_base = buf;
	bufs[0].iov_len = strlen(buf);

	send_msg.msg_iov = bufs;
	send_msg.msg_iovlen = 1;

	pcmsg ->cmsg_len = cmsglen;
	pcmsg ->cmsg_level = SOL_SOCKET;
	pcmsg ->cmsg_type= SCM_RIGHTS;
	*(int *)CMSG_DATA(pcmsg) = fd_to_send;
	send_msg.msg_control =pcmsg ;
	send_msg.msg_controllen =cmsglen;
	sendmsg(sockfd ,&send_msg ,0);
}

void recv_fd(int sockfd ,int *fd_to_recv)//接收文件描述符
{
	struct msghdr recv_msg;
	struct cmsghdr* pcmsg;

	int cmsglen = CMSG_LEN(sizeof(int));
	pcmsg = (struct cmsghdr*)calloc(1,cmsglen);
	struct iovec bufs[1];
	char buf[32]="";
	bufs[0].iov_base=buf;
	bufs[0].iov_len =32;

	recv_msg.msg_iov = bufs;
	recv_msg.msg_iovlen = 1;

	recv_msg.msg_control =pcmsg ;
	recv_msg.msg_controllen =cmsglen;
	recvmsg(sockfd ,&recv_msg ,0);
	*fd_to_recv = *(int*)CMSG_DATA(pcmsg);
}

int listen_socket(char *argv1,char* argv2)//分配端口，地址，然后监听
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

void handle_request(int fd_client)//子进程处理函数，收到命令对字符串简单处理后交给命令处理函数
{
	printf("handle_request!\n");
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
	}//客户端结束前会发送bye过来，接收到后退出while,打印客户端下线信息
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

void command_process(int fd_client ,MSG recv_msg)//对字符串处理判断，调用相应处理函数
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





