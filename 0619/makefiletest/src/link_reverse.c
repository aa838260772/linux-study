/*************************************************************************
	> File Name: link_reverse.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月19日 星期四 09时41分12秒
 ************************************************************************/
#include "linklist.h"
#include<stdio.h>
int main()
{
linklist h;
h=NULL;
link_create(&h);
show(h);
link_reverse(&h);
show(h);
return 0;
}


