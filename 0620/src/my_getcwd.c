/*************************************************************************
	> File Name: my_getcwd.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月20日 星期五 10时12分46秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
int main(int argc,char **argv)
{
//char* res=NULL;
//res=getcwd(NULL,0)
	printf("%s\n",getcwd(NULL,0));
//if(!res)
//perror("error location");

return 0;
}
