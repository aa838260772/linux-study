/*************************************************************************
	> File Name: my_chdir.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月20日 星期五 10时25分27秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
int main(int argc,char **argv)
{
int res;
if(argc==1)
 perror("too few argument!");
else
	res=chdir(argv[1]);
  printf("%s",getcwd(NULL,0));
if(res==-1)
   perror("unvaluable location!");




return 0;
}
