/*************************************************************************
	> File Name: itoa.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月19日 星期四 09时32分06秒
 ************************************************************************/

#include<stdio.h>
static void output(int );
int main()
{
int n;
printf("n:");
while(fflush(stdin),scanf("%d",&n))
{
	if(n<0)
{
putchar('-');
n=-1*n;
}
output(n);
printf("\n");
printf("n:");
}
return 0;
}
void output(int n)
{
int d;
if(n)
{
d=n;
n/=10;
output(n);
printf("%c",d%10+48);
}
}
