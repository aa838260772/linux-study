/*************************************************************************
	> File Name: mmyrmdir.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月20日 星期五 20时28分35秒
 ************************************************************************/

#include<stdio.h> 
#include<unistd.h>
#include<stdlib.h>
int main(int argc,char**argv)
{
int res;
if(argc==1)
 {
 printf("too few argument!\n");
 exit(-1);
 }
res=rmdir(argv[1]);
if(res==-1)
 perror("rmdir fail!");
return 0;
}

