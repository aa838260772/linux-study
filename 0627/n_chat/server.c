/*************************************************************************
  > File Name: server.c
  > Author: One
  > Mail:838260772@qq.com 
  > Created Time: 2014年06月27日 星期五 18时42分05秒
 ************************************************************************/

#include <stdio.h>
#include <sys/select.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#define N 500
typedef struct tag{
	char str[10];//记录进程号
	int fd_r;
	int fd_w;
}client;

int main()
{
	client cli[N];
	memset(cli,-1,sizeof(cli));
	int fd_server,fd_r,fd_w;
	fd_server=open("ser_fifo",O_RDONLY);//读方式打开服务器管道，获取上线请求
	fd_set fd_read,fd_ready;

	FD_ZERO(&fd_read);//初始化读集合
	FD_SET(fd_server,&fd_read);//连接进程写入读集合

	char buf[1024]="";
	char buf_read[32]="";
	char buf_write[32]="";

	while(1)
	{
		fd_ready=fd_read;

		int index,send_index,pid;
		select(1024,&fd_ready,NULL,NULL,NULL);
		if(FD_ISSET(fd_server,&fd_ready))//如果有进程请求
		{
			memset(buf,0,1024);
			if(read(fd_server,buf,1024)==0)//获取客户端请求时发送过来的pid
				continue;
			pid=atoi(buf);
			printf("%s is on line!\n",buf);

			sprintf(buf_write,"%d_read.fifo",pid);//打开客户端的读管道来写
			sprintf(buf_read,"%d_write.fifo",pid);//打开客户端的写管道来读

			printf("%s   %s \n",buf_write,buf_read);
			fd_w=open(buf_write,O_WRONLY);
			fd_r=open(buf_read,O_RDONLY);
			printf("fd_w:%d fd_r:%d\n",fd_w,fd_r);
			for(index=0;index<N;++index)//分配结构体数组存储管道文件描述符
			{
				if(cli[index].fd_r==-1)
					break;
			}
			if(index<N)
			{
				cli[index].fd_r=fd_r;
				cli[index].fd_w=fd_w;
				strncpy(cli[index].str,buf,10);
			}else
			{
				kill(pid,9);
				close(fd_r);
				close(fd_w);
				unlink(buf_read);
				unlink(buf_write);
			}
			FD_SET(cli[index].fd_r,&fd_read);//客户端的写管道加入读集合
		}

		for(index=0;index<N;++index)
		{
			if(FD_ISSET(cli[index].fd_r,&fd_ready))
			{
			
				memset(buf_read,0,1024);
				memset(buf,0,1024);
				memset(buf_write,0,1024);
				if(read(cli[index].fd_r,buf_read,1024)==0)
					continue;
				if(strcmp(buf_read,"bye")==0)//某个客户端要求退出
				{   
					pid=atoi(cli[index].str);
					printf("%d is off\n",pid);
                        fflush(stdout);
					close(cli[index].fd_r);
					close(cli[index].fd_w);//关闭客户端的管道
					FD_CLR(cli[index].fd_r,&fd_read);
					cli[index].fd_r=cli[index].fd_w=-1;//回收文件描述符数组
					strcpy(cli[index].str,"");
				}
				else
				{
					for(send_index=0;send_index<N;++send_index)
						if(send_index!=index)
						{
							write(cli[send_index].fd_w,buf_read,strlen(buf_read));
						}
				}
			}
		}
	}
	return 0;
}
