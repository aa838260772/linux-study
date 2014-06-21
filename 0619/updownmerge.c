/*************************************************************************
	> File Name: updownmerge.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月19日 星期四 10时22分08秒
 ************************************************************************/

#include<stdio.h>
#include"linklist.h"
int main()
{
linklist h1,h2;
h1=h2=NULL;
printf("linklist 1:");
link_create(&h1);
printf("linklist 2:");
fflush(stdin);
link_create(&h2);
link_reverse(&h2);
link_merge(&h1,&h2);

return 0;
}
