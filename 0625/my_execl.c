/*************************************************************************
	> File Name: my_execl.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月25日 星期三 14时44分00秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
int main(int argc,char **argv)
{
printf("begin!\n");
//execl("/bin/ls","ls","-l",NULL);
//execlp("ls","ls","-l",NULL);//在标准路径下去找
//char *arglist[]={"./hello","hello","world",NULL};
char **arglist;
int i;
arglist=(char**)malloc((argc+1)*sizeof(char*));
for(i=0;i<argc;++i)
{
arglist[i]=argv[i];
}
argv[i]=NULL;
execvp(arglist[0],arglist+1);
printf("end\n");

return 0;
}

