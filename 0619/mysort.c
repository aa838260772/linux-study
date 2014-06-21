/*************************************************************************
	> File Name: mysort.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月19日 星期四 14时12分06秒
 ************************************************************************/

#include<stdio.h>
#include "mysort.h"
static int partion(int *,int );
void bubble_sort(int *a,int len)
{
int i,j;
for(i=0;i<len-1;++i)
for(j=0;j<len-i-1;++j)
if(a[j]>a[j+1])
{
a[j]^=a[j+1];
a[j+1]^=a[j];
a[j]^=a[j+1];
}
}

void select_sort(int *a,int len)
{
int i,j;
int key;
for(i=0;i<len;++i)
{
	key=i;
for(j=i+1;j<len;++j)
	if(a[j]<a[key])
            key=j;

if(i!=key)
{
	a[i]^=a[key];
    a[key]^=a[i];
    a[i]^=a[key];
}
}
}

void insert_sort(int *a,int len)
{
int i,j;
int temp;
for(i=1;i<len;++i)
if(a[i]<a[i-1])
{
temp=a[i];
for(j=i-1;j>=0&&a[j]>temp;--j)
 a[j+1]=a[j];
a[j+1]=temp;
}
}

void quick_sort(int *a,int len)
{
int p;
if(len>1)
{
p=partion(a,len);
quick_sort(a,p);
quick_sort(a+p+1,len-p-1);
}
}

int partion(int *a,int len)
{
int low,high,key;
key=a[0];
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
if(low<high)
	a[high]=a[low];
}
a[low]=key;
return low;
}

void show(char *str,int *a,int len)
{
	int i;
fputs(str,stdout);
for(i=0;i<len;++i)
printf("%d ",a[i]);

printf("\n");
}












