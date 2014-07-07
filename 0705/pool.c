/*************************************************************************
  > File Name: pool.c
  > Author: One
  > Mail:838260772@qq.com 
  > Created Time: 2014年07月05日 星期六 16时57分34秒
 ************************************************************************/

#include "pool.h"
static void child_main(int,int);
int make_main(CHLD *arr,int cnt)
{
	int fd_max=0x80000000;
	pid_t pid;
	int index;
	for(index = 0 ; index < cnt ; index++)
	{
		int fds1[2];
		int fds2[2];
		pipe(fds1);
		pipe(fds2);
		pid=fork();
		if(pid==0)
		{
			close(fds1[1]);
			close(fds2[0]);
			//dup2(fds1[0],0);
			//dup2(fds2[1],1);
			//close(fds1[0]);
			//close(fds2[1]);
			child_main(fds2[1],fds1[0]);
		}else
		{
			close(fds1[0]);
			close(fds2[1]);
			arr[index].s_pid=pid;
			arr[index].s_read=fds2[0];
			arr[index].s_write=fds1[1];
			arr[index].s_cnt=0;
			arr[index].s_status=S_IDLE;
			if(fd_max<fds2[0])
				fd_max=fds2[0];
		}
	}
	return fd_max;
}

void child_main(int fd_w,int fd_r)
{
	SA client_addr;
	char buf[MSG_LEN];
	char buf1[MSG_LEN];
	while(1)
	{
		bzero(&client_addr,sizeof(SA));
	client_addr.sin_family=AF_INET;
		bzero(buf,MSG_LEN);
		bzero(buf1,MSG_LEN);
		FILE *fp = fdopen(fd_r ,"r");
		fscanf(fp,"%d %d %s",&(client_addr.sin_addr.s_addr),&(client_addr.sin_port),buf);
       read(fd_r,buf1,MSG_LEN);
		//puts(buf);
		puts(buf1);

		printf("%d %d\n",client_addr.sin_addr.s_addr,client_addr.sin_port);
		int fd_server=socket(AF_INET,SOCK_DGRAM,0);
		sendto(fd_server ,buf ,strlen(buf) ,0 ,(struct sockaddr*)&client_addr ,sizeof(SA));
		write(fd_w,"1",1);
		fflush(stdout);
	}
}

