/*************************************************************************
  > File Name: pass_fd.c
  > Author: One
  > Mail:838260772@qq.com 
  > Created Time: 2014年07月07日 星期一 21时29分26秒
 ************************************************************************/
//实现父进程向子进程传递文件描述符
#include <stdio.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <signal.h>
void send_fd(int sockfd ,int fd_to_send);
void recv_fd(int sockfd ,int *fd_to_recv);
void my_handle(int num)
{
	wait();
	exit(0);
}

int main(int argc ,char **argv)
{
	pid_t pid;
	int fds[2];
	socketpair(AF_LOCAL ,SOCK_STREAM ,0,fds);//建立一对匿名的已经连接的套接字
	pid = fork();
	if(pid > 0)
	{
		close(fds[0]);
		signal(17 ,my_handle);
		int fd_file = open(argv[1], O_RDONLY);
		send_fd(fds[1] ,fd_file);
	}else
	{
		close(fds[1]);
		int fd_file;
		recv_fd(fds[0] ,&fd_file);
		FILE *fp =fdopen(fd_file , "r");
		char line[1024];
		while(bzero(line ,1024) ,fgets(line ,1024 ,fp) != NULL)
		{
			puts(line);
		}
		fclose(fp);
	}
	return 0;
}

void send_fd(int sockfd ,int fd_to_send)//实现通过双向管道传送
{
	struct msghdr send_msg;
	struct cmsghdr* pcmsg;
	int cmsglen = CMSG_LEN(sizeof(int));
	pcmsg = (struct cmsghdr*)calloc(1 ,cmsglen);
	bzero(&send_msg ,sizeof(send_msg));
	send_msg.msg_name = NULL;
	send_msg.msg_namelen = 0;
	send_msg.msg_flags = 0;
	char buf[1]=" ";
	struct iovec bufs[1];
	bufs[0].iov_base = buf ;
	bufs[0].iov_len = strlen(buf);

    send_msg.msg_iov = bufs;
	send_msg.msg_iovlen = 1;

	pcmsg -> cmsg_len = cmsglen;
	pcmsg -> cmsg_level = SOL_SOCKET;
	pcmsg -> cmsg_type =SCM_RIGHTS;
	*(int *)CMSG_DATA(pcmsg)=fd_to_send;
	send_msg.msg_control = pcmsg;
	send_msg.msg_controllen = cmsglen;

	sendmsg(sockfd ,&send_msg ,0);
}

void recv_fd(int sockfd ,int *fd_to_recv)
{
	struct msghdr recv_msg;
	struct cmsghdr* pcmsg;
	int cmsglen = CMSG_LEN(4);
	pcmsg = (struct cmsghdr*)calloc(1 , cmsglen);
	struct iovec bufs[1];
	char buf[1]="";
	bufs[0].iov_base = buf;
	bufs[0].iov_len = 1;

	recv_msg.msg_iov = bufs ;
	recv_msg.msg_iovlen = 1;
	recv_msg.msg_control = pcmsg;
	recv_msg.msg_controllen =cmsglen ;
	recvmsg(sockfd ,&recv_msg ,0);
	//printf("buf: %s \n",buf);
	*fd_to_recv = *(int*)CMSG_DATA(pcmsg);
}


