/*************************************************************************
	> File Name: word_reverse.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月26日 星期四 10时19分41秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
void word_reverse(char *,int,int);
char buf[1024];
int i,j;
while(memset(buf,0,1024),fgets(buf,1024,stdin)!=NULL)
{
	if(buf[0]!='\n')
		buf[strlen(buf)-1]='\0';//处理掉读入的空格

   word_reverse(buf,0,strlen(buf)-1);//整个字符串逆转

i=0;j=0;
while(buf[j]!='\0')
{
while(buf[j]==' '&&buf[j]!='\0')
	j++;//找到第一个非空格
if(buf[j]!='\0')
	i=j;//i在单词头
while(buf[j]!=' '&&buf[j]!='\0')
	j++;//找到单词后第一个空格
word_reverse(buf,i,j-1);//逆转

}
printf("after reverse:\n");
fputs(buf,stdout);
printf("\n");
}
return 0;
}

void word_reverse(char* a,int i,int j)
{
while(i<j)
{
a[i]^=a[j];
a[j]^=a[i];
a[i]^=a[j];
i++;
j--;
}
}
