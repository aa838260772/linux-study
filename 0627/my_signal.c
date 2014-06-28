/*************************************************************************
	> File Name: my_signal.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月27日 星期五 09时49分29秒
 ************************************************************************/

#include <stdio.h>
#include <signal.h>
void  my_handler(int num)
{
printf("sigal num:%d\n",num);
}
int main()
{
signal(2,my_handler);

while(1)
{
printf("hello\n");
sleep(1);
}
return 0;
}
