/*************************************************************************
	> File Name: test1.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月28日 星期六 16时01分52秒
 ************************************************************************/

#include<stdio.h>
int main()
{

printf("core dump\n");
*(char*)0=0;
return 0;
}