/*************************************************************************
	> File Name: quick_sort.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月18日 星期三 14时10分21秒
 ************************************************************************/

#include "sort.h"
static int partion(int *,int);
void quick_sort(int *a,int len)
{
	int k;
if(len>1)
{
k=partion(a,len);
quick_sort(a,k);
quick_sort(a+k+1,len-k-1);
}
}
int partion(int *a,int len)
{
int key,low,high;
key=*a;
low=0;
high=len-1;
while(low<high)
{
while(low<high&&a[high]>=key)
        high--;
if(low<high)
	a[low]=a[high];
while(low<high&&a[low]<key)
	low++;
a[high]=a[low];
}
a[low]=key;
return low;
}





