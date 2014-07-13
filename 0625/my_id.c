/*************************************************************************
	> File Name: my_id.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月25日 星期三 10时17分56秒
 ************************************************************************/

#include<stdio.h>
int main()
{
printf("uid:%d gid:%d pid:%u ppid:%u euid:%d egid:%d\n",getuid(),getgid(),
		getpid(),getppid(),geteuid(),getegid());
while(1);
return 0;
}
