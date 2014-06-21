/*************************************************************************
	> File Name: mycd.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月20日 星期五 20时32分54秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(int argc,char **argv)
{
	int res;
if(argc==1)
{
printf("too few argument !\n");
exit(-1);
}
res=chdir(argv[1]);
printf("%s\n",getcwd(NULL,0));
if(res==-1)
perror("chdir fail!");

return 0;
}
