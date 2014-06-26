/*************************************************************************
	> File Name: my_popen.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月26日 星期四 09时32分48秒
 ************************************************************************/

#include<stdio.h>
int main()
{
FILE *fp;
int read_n;
char buf[1024]="";
fp=popen("ls -l ","r");
read_n=fread(buf,1,1024,fp);
fputs(buf,stdout);
//puts(buf);
//fwrite(buf,1,read_n,stdout);
pclose(fp);
return 0;
}
