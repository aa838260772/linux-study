/*************************************************************************
	> File Name: sorttest.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月19日 星期四 14时28分03秒
 ************************************************************************/

#include<stdio.h>
#include"mysort.h"
#include<time.h>
#include<string.h>
int main()
{
int a[MAX],b[MAX],c[MAX],d[MAX];
int i,j;
srand(time(NULL));
for(i=0;i<20;++i)
{
a[i]=rand()%500;
b[i]=a[i];
c[i]=a[i];
d[i]=a[i];
}
show("sorce:",a,20);
bubble_sort(a,20);
show("bubble",a,20);
select_sort(b,20);
show("select",b,20);
insert_sort(c,20);
show("insert",c,20);
quick_sort(d,20);
show("quick",d,20);
return 0;
}
