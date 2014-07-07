/*************************************************************************
  > File Name: server_poll.c
  > Author: One
  > Mail:838260772@qq.com 
  > Created Time: 2014年07月06日 星期日 10时40分29秒
 ************************************************************************/

#include "pool.h"
int main(int argc ,char * argv[])
{
	if(4 != argc)
	{
		printf("EXE IP PORT CNT");
		exit(-1);
	}

	int fd_server;
	fd_server=socket(AF_INET,SOCK_DGRAM,0);

	SA server_addr,client_addr;
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(atoi(argv[2]));
	server_addr.sin_addr.s_addr=inet_addr(argv[1]);
	if(-1 == bind(fd_server ,(const struct sockaddr*)&server_addr,sizeof(SA)))
	{
		perror("bind!\n");
		close(fd_server);
		exit(-1);
	}

	int fd_max,cnt=atoi(argv[3]);
	PCHLD childs=(PCHLD)calloc(cnt,sizeof(CHLD));
	fd_max = make_child(childs,cnt);
	if(fd_server > fd_max)
		fd_max = fd_server;

	fd_set fd_read,fd_ready;
	FD_ZERO(&fd_read);
	FD_SET(fd_server,&fd_read);

	int addr_len = sizeof(SA);
	struct timeval tm;
	int index;

	char buf[MSG_LEN];
	for(index =0 ;index <cnt;index++)
	{
		FD_SET(childs[index].s_read,&fd_read);
	}
	while(1)
	{
		fd_ready=fd_read;
		tm.tv_sec=0;
		tm.tv_usec=1000;

		select(fd_max,&fd_ready,NULL,NULL,&tm);
		bzero(buf,MSG_LEN);
		bzero(&client_addr,sizeof(SA));
		if(FD_ISSET(fd_server,&fd_ready))
		{
			recvfrom(fd_server,buf,MSG_LEN,0,(struct sockaddr*)&client_addr,&addr_len);
			for(index = 0; index <cnt; index++)
			{
				if(childs[index].s_status == S_IDLE) 
					break;
			} 

			if(index != cnt)
			{
				childs[index].s_status == S_BUSY;
				FILE *fp = fdopen(childs[index].s_write,"w");
				printf("%s %x %d %s\n",inet_ntoa(client_addr.sin_addr),client_addr.sin_addr.s_addr,client_addr.sin_port,buf);
				fprintf(fp,"%x %d %s\n",client_addr.sin_addr.s_addr,client_addr.sin_port,buf);//用字符串形式传递
				fflush(fp);
			}

		}
		for(index =0 ;index <cnt ;index++)
		{
			if(FD_ISSET(childs[index].s_read,&fd_ready))
			{
				char ch;
				read(childs[index].s_read,&ch,1);
				childs[index].s_status =S_IDLE;
			}
		}
	}
	return 0;
}

