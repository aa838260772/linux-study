/*************************************************************************
	> File Name: test.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月28日 星期六 15时30分11秒
 ************************************************************************/

#include<stdio.h>
int func(int a)
{
int i=0;
int sum=0;
for(i=1;i<=a;++i){
sum+=i;
}
return sum;
}

int main()
{
int i=0;
int a=10;
int s=func(a);
printf("sum is :%d\n",s);
return 0;
}


