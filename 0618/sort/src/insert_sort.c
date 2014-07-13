/*************************************************************************
	> File Name: insert_sort.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月18日 星期三 14时10分21秒
 ************************************************************************/

#include "sort.h"
void insert_sort(int *a,int len)
{
int i,j,temp;
for(i=1;i<len;++i)
if(a[i]<a[i-1])
{
temp=a[i];
for(j=i-1;j>=0&&a[j]>temp;--j)
a[j+1]=a[j];
a[j+1]=temp;
}
}

