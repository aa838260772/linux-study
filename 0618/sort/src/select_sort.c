/*************************************************************************
	> File Name: select_sort.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月18日 星期三 13时59分16秒
 ************************************************************************/

#include "sort.h"
void select_sort(int *a,int len)
{
int i,j,key;
for(i=0;i<len;++i)
{
key=i;
for(j=i+1;j<len;++j)
if(a[j]<a[key])
key=j;
if(i!=key)
{
a[key]^=a[i];
a[i]^=a[key];
a[key]^=a[i];
}
}
}
