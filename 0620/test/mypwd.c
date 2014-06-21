/*************************************************************************
	> File Name: mypwd.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月20日 星期五 20时16分40秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
int main(int argc,char **argv)
{

printf("%s\n",getcwd(NULL,0));

return 0;
}
