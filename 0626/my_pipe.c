/*************************************************************************
	> File Name: my_pipe.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月26日 星期四 15时25分35秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
char buf[256];
int fd1[2];//实现子进程写，父进程读
int fd2[2];//实现父进程读，子进程写
memset(buf,0,256);

if(pipe(fd1)==-1)//建立两个管道，fd1[0]为读，fd1[1]为写
{
printf("create pipe fail!\n");
exit(1);
}

if(pipe(fd2)==-1)
{
printf("create pipe fail!\n");
exit(1);
}
printf("fd1[0];%d fd1[1]:%d fd2[0]:%d fd2[1]:%d\n",fd1[0],fd1[1],fd2[0],fd2[1]);

if(fork()>0)//父进程
{
close(fd1[1]);//在父读的时候关闭父写管道
close(fd2[0]);//在父写的时候关闭父读管道
	printf("parent first!\n");
	printf("read_n:%d\n",strlen(buf));
while(memset(buf,0,256),read(fd1[0],buf,sizeof(buf))>0)
{
printf("child say:");
fflush(stdout);
write(1,buf,sizeof(buf));
fflush(fdopen(fd1[0],"r"));
}//按ctrl+d时退出父读子写，进入下面的父写子读的过程
close(fd1[0]);

while(memset(buf,0,256),fgets(buf,256,stdin)!=NULL)
{
write(fd2[1],buf,sizeof(buf));
}
close(fd2[1]);

wait(NULL);
exit(0);
}
else
{
	printf("child first!\n");
close(fd1[0]);
close(fd2[1]);
while(memset(buf,0,256),fgets(buf,256,stdin)!=NULL)
{
//write(fd1[1],buf,sizeof(buf));
FILE *fp=fdopen(fd1[1],"w");
fprintf(fp,"%s",buf);
fflush(fp);
}
close(fd1[1]);

while(memset(buf,0,256),read(fd2[0],buf,sizeof(buf))>0)
{
printf("father say:");
fflush(stdout);
write(1,buf,sizeof(buf));
}
close(fd2[0]);
exit(0);
}
return 0;
}

