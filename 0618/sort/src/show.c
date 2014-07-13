/*************************************************************************
	> File Name: show.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月18日 星期三 16时09分11秒
 ************************************************************************/

#include "sort.h"
void show(int *a,int len)
{
int i;
for(i=0;i<len;++i)
{
printf("%3d ",a[i]);
if(i!=0&&i%9==0)
printf("\n");
}
printf("\n");
}

