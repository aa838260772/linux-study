/*************************************************************************
  > File Name: client.c
  > Author: One
  > Mail:838260772@qq.com 
  > Created Time: 2014年07月01日 星期二 20时29分04秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
void handle(int num)
{
	wait(NULL);
	exit(0);
}
int main()
{
	int fd_server,fd_r;
	FILE *fp;
	char buf[1024];
	char buf_r[32];

	int pid=getpid();
	sprintf(buf_r,"%d_read.fifo",pid);

	mkfifo(buf_r,0666);

	fd_server=open("ser.fifo",O_WRONLY);
	fp=fdopen(fd_server,"w");
	fprintf(fp,"%d",pid);

	int sid;
		if((sid=fork())>0)
		{
			printf("client!\n");
			signal(17,handle);
			while(memset(buf,0,1024),fgets(buf,1024,stdin)!=NULL)
			{
				printf("111\n");
             fd_r=open(buf_r,O_RDONLY);
            fprintf(fp,"%d %s",pid,buf);
              fflush(fp);
			 write(fd_r,buf,strlen(buf));
			  puts(buf);
			}
			unlink(buf_r);
			kill(9,sid);
			wait();
			exit(0);
		}else{
			while(memset(buf,0,1024),read(fd_r,buf,1024)>0)
			{
				fprintf(stdout,buf,NULL);
				fflush(stdout);
			}
			unlink(buf_r);
		}
	return 0;
}






















