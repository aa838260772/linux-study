/*************************************************************************
  > File Name: server_processpool.c
  > Author: One
  > Mail:838260772@qq.com 
  > Created Time: 2014年07月03日 星期四 19时33分43秒
 ************************************************************************/

#include <stdio.h>
#include <my_child.h>
#include "msg.h""
int main(int argc,char *argv[])
{
	signal(13,SIG_IGN);
	if(argc!=4)
	{
		printf("USAFE : EXE IP PORT CNT\n");
		exit(-1);
	}
	int fd_server;
	fd_set fd_read,fd_ready;

	pCHLD my_chlds=(pCHLD)calloc(atoi(argv[3]),sizeof(char));
	make_chld(my_chlds,atoi(argv[3]));//创建argv[3]个子进程
	
	fd_server=listen_fd(argv[1],argv[2]);// 父进程负责监听

	FD_ZERO(&fd_read);
	FD_SET(fd_server,&fd_read);
   
	int index;
	for(index =0 ; index < atoi(argv[3]); index++)
	{
		FD_SET(my_chlds[index].s_read,&fd_read);
	}//子进程的读描述符加入监听队列

	struct timeval tm;
	while(1)
	{
		tm.tv_usec=1000;
		tm.tv_sec=0;
		fd_ready=fd_read;
		select(1024,&fd_ready,NULL,NULL,&tm);
		if(FD_ISSET(fd_server,&fd_ready))
		{
			int fd_client = accept(fd_server,NULL,NULL);//不关心地址，可以不要
            printf("%d\n",fd_client);
			for(index =0 ;index < atoi(argv[3]) ; index++)
               if(index!=fd_server)
			   {
			   if(my_chlds[index].s_status==S_IDLE)
			   {
				write(my_chlds[index].s_read,&fd_client,sizeof(int));
			   my_chlds[index].s_status=S_BUSY;
			   FD_SET(my_chlds[index].s_pid,&fd_read);//加入轮询
			   }
			   }
		}
		for(index = 0 ; index < atoi(argv[3]) ; index++ )
		{
			if(FD_ISSET(my_chlds[index].s_read,&fd_ready))
			{
				//read_from_fd();
				char buf[20]="";
				read(my_chlds[index].s_read,buf,20);
			
				FD_CLR(my_chlds[index].s_read,&fd_read);
				my_chlds[index].s_status = S_IDLE;
			}
		}
	}
}
