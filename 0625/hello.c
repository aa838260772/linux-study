/*************************************************************************
	> File Name: hello.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月25日 星期三 11时20分29秒
 ************************************************************************/

#include<stdio.h>
int main(int argc,char **argv)
{

int i;
for(i=0;i<argc;++i)
printf("argv[%d]: %s\n",i,argv[i]);

return 0;
}
