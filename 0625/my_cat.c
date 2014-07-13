/*************************************************************************
	> File Name: my_cat.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月25日 星期三 11时17分52秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(int argc,char **argv)
{
char buf[256];
memset(buf,0,256);
//sprintf(buf,"%s","cat");
int i;
for(i=1;i<argc;++i)
{
//strcat(buf," ");
//strcat(buf,argv[i]);
sprintf(buf,"%s %s",buf,argv[i]);
}
//sprintf(buf,"%s %s","cat",argv[1]);
system(buf);
return 0;
}
