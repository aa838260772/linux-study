/*************************************************************************
  > File Name: pool_server.c
  > Author: One
  > Mail:838260772@qq.com 
  > Created Time: 2014年07月05日 星期六 22时45分51秒
 ************************************************************************/

#include "pool.h"
int main(int argc , char * argv[])
{
	if(4 != argc)
	{
		printf("EXE  ip  port  cnt");
		exit(-1);
	}

	int fd_server;
	SA server_addr,client_addr;

	fd_server=socket(AF_INET,SOCK_DGRAM,0);
	if(fd_server == -1)
	{
		perror("socket\n");
		exit(-1);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	server_addr.sin_port = htons( atoi(argv[2]) );

	if(-1 == bind(fd_server,(const struct sockaddr*)&server_addr,sizeof(SA)))
	{
		perror("bind!\n");
		exit(-1);
	}

	CHLD *childs = (CHLD*)calloc( atoi(argv[3]) , sizeof(CHLD));
	int fd_max = make_main(childs , atoi(argv[3]));
     if(fd_server > fd_max)
		   fd_max = fd_server;

	fd_set fd_read,fd_ready;
	FD_ZERO(&fd_read);
	FD_SET(fd_server,&fd_read);
	struct timeval tm;

   for(index = 0; index < atoi(argv[3]);index++)
   {
   FD_SET(childs[index].s_read,&fd_read);
   }

	int addr_len = sizeof(client_addr);
	int index;
	while(1)
	{
		fd_ready = fd_read;
		tm.tv_sec = 0;
		tm.tv_usec = 1000;
		char buf[MSG_LEN]="";
   
		select(fd_max+1 ,&fd_ready ,NULL ,NULL ,&tm);

		if(FD_ISSET(fd_server,&fd_ready))
		{
			printf("1111\n");
			recvfrom(fd_server ,buf ,MSG_LEN ,0 ,(struct sockaddr*)&client_addr ,&addr_len);//接收请求
			for(index = 0 ;index < atoi(argv[3]) ;index++)//找到一个空闲的
			{
				if(childs[index].s_status == S_IDLE)
					break;
			}

			if(index != atoi(argv[3]))//把地址送到子进程，
			{
		     	printf("%s\n",buf);
				childs[index].s_status == S_BUSY;
				FILE *fp=fdopen(childs[index].s_write ,"w") ;
				printf("%s %d\n",inet_ntoa(client_addr.sin_addr),client_addr.sin_port);
			
		printf("%d %d\n",client_addr.sin_addr.s_addr,client_addr.sin_port);
				fprintf(fp ,"%d %d %s" ,client_addr.sin_addr.s_addr,client_addr.sin_port,buf );
				fflush(fp);
			//	printf("%d %d %s" ,client_addr.sin_addr ,client_addr.sin_port ,buf );
			
			}
		}
		for(index = 0 ; index < atoi(argv[3]) ;index++ )//监听是否有子进程完成
		{
			char ch;
			if(FD_ISSET(childs[index].s_read ,&fd_ready))
			{
				read(childs[index].s_read,&ch,1) ;
				childs[index].s_status=S_IDLE;
			}
		}
	}
	return 0;
}





