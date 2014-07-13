/*************************************************************************
	> File Name: bubble_sort.c
	> Author: One
	> Mail:838260772@qq
	> Created Time: 2014年06月18日 星期三 13时58分24秒
 ************************************************************************/
#include "sort.h"
void bubble_sort(int *a,int len)
{
int i,j;
for(i=1;i<len;++i)
{
 for(j=0;j<len-i;++j)
	 if(a[j]>a[j+1])
     {
      a[j]^=a[j+1];
	  a[j+1]^=a[j];
	  a[j]^=a[j+1];
	 }
}
}
