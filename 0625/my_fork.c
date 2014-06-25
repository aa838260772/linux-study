/*************************************************************************
	> File Name: my_fork.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月25日 星期三 14时04分21秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main()
{
pid_t iret,iwait;
iret=fork();
if(iret==0)
{
printf("child:%u  pid:%d  ppid:%d \n",iret,getpid(),getppid());
sleep(20);
printf("child exit!\n");
printf("child:%u  pid:%d  ppid:%d \n",iret,getpid(),getppid());
}
else
{
printf("father:%u  pid:%d  ppid:%d \n",iret,getpid(),getppid());
sleep(8);
printf("strating wait!\n");
iwait=wait(NULL);
printf("pid:%u end!\n",iwait);
printf("ending wait!\n");
printf("father exit!\n");
}
return 0;
}
