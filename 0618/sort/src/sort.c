/*************************************************************************
	> File Name: sort.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月18日 星期三 14时26分32秒
 ************************************************************************/

#include<stdio.h>
#include "sort.h"
#include<time.h>
#include<stdlib.h>
int main()
{
int a[LEN],b[LEN],c[LEN],d[LEN];
int i;
srand(time(NULL));
for(i=0;i<LEN;++i)
{
//a[i]=rand()%500;
scanf("%d",&a[i]);
b[i]=a[i];
c[i]=a[i];
d[i]=a[i];
}
show(a,LEN);
bubble_sort(a,LEN);
insert_sort(b,LEN);
select_sort(c,LEN);
quick_sort(d,LEN);
printf("bubble:\n");
show(a,LEN);
printf("insert:\n");
show(b,LEN);
printf("select:\n");
show(c,LEN);
printf("quick :\n");
show(d,LEN);
return 0;
}

