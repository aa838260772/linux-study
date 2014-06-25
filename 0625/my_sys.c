/*************************************************************************
	> File Name: my_sys.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月25日 星期三 11时50分36秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(int argc,char **argv)
{
char buf[256];
int i;
sprintf(buf,"%s","./hello");
for(i=1;i<argc;i++)
{
strcat(buf," ");
strcat(buf,argv[i]);
}
system(buf);
return 0;
}
