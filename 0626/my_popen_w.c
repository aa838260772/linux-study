/*************************************************************************
	> File Name: my_popen_w.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月26日 星期四 10时35分39秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
FILE *fp;
fp=popen("./word_reverse","w");//管道写定向到可执行文件word_reverse
char buf[1024];
while(memset(buf,0,1024),fgets(buf,1024,stdin)!=NULL)
{
//fprintf(fp,"%s",buf);
fwrite(buf,1,strlen(buf),fp);
fflush(fp);
}
pclose(fp);
return 0;
}
