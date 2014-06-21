/*************************************************************************
	> File Name: mymkdir.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月20日 星期五 20时20分45秒
 ************************************************************************/

#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>
int main(int argc,char **argv)
{
	int res;
if(argc==1)
{
printf("too few arguments!\n");
exit(-1);
}
res=mkdir(argv[1],0777&~umask);
if(res==-1)	
	perror("mkdir error!");
	
	
	
	
	
return 0;	
}

