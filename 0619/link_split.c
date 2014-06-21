/*************************************************************************
	> File Name: link_split.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月19日 星期四 14时00分10秒
 ************************************************************************/

#include<stdio.h>
#include"linklist.h"
int main()
{
linklist h1,h2;
h1=h2=NULL;
printf("h1:");
link_create(&h1);
link_split(&h1,&h2);
show(h1);
show(h2);
return 0;
}
