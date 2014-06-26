/*************************************************************************
	> File Name: my_fdopen.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月26日 星期四 09时43分03秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main()
{
int fd;
FILE *fp;
fd=open("a.txt",O_WRONLY|O_CREAT,0666);
fp=fdopen(fd,"w");
fprintf(fp,"%s %s %s","hello","how","are");
return 0;
}
