/*************************************************************************
  > File Name: pool.c
  > Author: One
  > Mail:838260772@qq.com 
  > Created Time: 2014年07月06日 星期日 10时08分56秒
 ************************************************************************/

#include "pool.h"
static void main_child(int ,int );
int make_child(PCHLD arr ,int cnt)
{
	pid_t pid;
	int index;
	int fd_max=0x80000000;
	for(index =0 ; index < cnt ;index++)
	{
		int fds1[2];
		int fds2[2];
		pipe(fds1);
		pipe(fds2);

		pid=fork();
		if(pid==0)//子进程进入main_child
		{
			close(fds1[0]);
			close(fds2[1]);
			main_child(fds2[0],fds1[1]);
		}else//父进程管理进程列表
		{
			close(fds1[1]);
			close(fds2[0]);
			arr[index].s_read=fds1[0];
			arr[index].s_write=fds2[1];
			arr[index].s_status=S_IDLE;
			arr[index].s_cnt=0;
			if(fds1[0]>fd_max)
				fd_max = fds1[0];
		}
	}
	return fd_max;
}

void main_child(int  fd_r,int fd_w)
{
	char buf[MSG_LEN]="";
	SA client_addr;
	int fd_socket;
	while(1)
	{
		bzero(&client_addr,sizeof(SA));
		client_addr.sin_family = AF_INET;
		bzero(buf,MSG_LEN);
		// read(fd_r,buf,MSG_LEN);
		//puts(buf);
		fd_socket = socket(AF_INET , SOCK_DGRAM,0);
		FILE *fp=fdopen(fd_r,"r");
		fscanf(fp,"%x %d %s",&(client_addr.sin_addr.s_addr),&(client_addr.sin_port),buf);//这里有问题，用字符串形式形式取试试。
		//read(fd_r,buf,MSG_LEN);
		//puts(buf);
		//sscanf(buf,"%d %d %s",&(client_addr.sin_addr.s_addr),&(client_addr.sin_port),buf);

		printf("system:%u\n",inet_addr("192.168.1.138"));
		printf("%s %x %d %s\n",inet_ntoa(client_addr.sin_addr),client_addr.sin_addr.s_addr,client_addr.sin_port,buf);
		sendto(fd_socket,buf,strlen(buf),0,(const struct sockaddr*)&client_addr,sizeof(SA));
		write(fd_w,"1",1);
	}

}






