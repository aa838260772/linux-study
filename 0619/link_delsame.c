/*************************************************************************
	> File Name: link_delsame.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月19日 星期四 11时03分17秒
 ************************************************************************/

#include<stdio.h>
#include"linklist.h"
int main()
{
linklist h1,h2;
h1=h2=NULL;
printf("linklist 1:");
link_create(&h1);
fflush(stdin);
printf("linklist 2:");
link_create(&h2);
link_delsame(&h1,&h2);
show(h1);
return 0;
}
