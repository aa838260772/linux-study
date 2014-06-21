/*************************************************************************
	> File Name: my_rmdir.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月20日 星期五 10时02分52秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(int argc,char **argv)
{
	int res=0;
printf("%s",argv[0]);
	//printf("%d\n",argc);
if(argc==1)
{
printf("too few argu!\n");
  return 1;

}
   res=rmdir(argv[1]);
if(res==-1)
	perror("rmdir error!\n");




return 0;
}
