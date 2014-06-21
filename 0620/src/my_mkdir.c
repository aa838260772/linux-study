/*************************************************************************
	> File Name: my_mkdir.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月20日 星期五 09时38分53秒
 ************************************************************************/

#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>
int main(int argc ,char * argv[])
{
int iret;
if(argc==1)
{
printf("too few arg!\n");
exit(-1);
}
else
{
iret = mkdir(argv[1],0777);
}
if(iret==-1)
	perror("mkdir error!");
return 0;

}
