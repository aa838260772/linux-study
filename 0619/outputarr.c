/*************************************************************************
	> File Name: outputarr.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月19日 星期四 10时01分06秒
 ************************************************************************/

#include<stdio.h>
#define N 256
int main()
{
int a[N];
int buf=0xffffffff;
int i=0,j;
while(fflush(stdin),scanf("%d",&a[i]))
{
i++;
}
for(j=0;j<i;++j)
if(a[j]!=buf)
{
buf=a[j];
printf("%3d ",a[j]);
}
printf("\n");
return 0;
}
