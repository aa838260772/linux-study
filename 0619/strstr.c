/*************************************************************************
	> File Name: strstr.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月19日 星期四 11时09分27秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define STR_LEN 256
int main()
{
char str[STR_LEN];
char sub_str[STR_LEN];
memset(str,0,sizeof(str));
memset(sub_str,0,sizeof(sub_str));
int i,j,k;
printf("str:");
fgets(str,sizeof(str),stdin);
fflush(stdin);
printf("sub_str:");
fgets(sub_str,sizeof(sub_str),stdin);

for(i=0;str[i]!='\n';i++)
{
k=i;
for(j=0;sub_str[j]!='\n'&&str[k]!='\n';++j)
{
	if(sub_str[j]!=str[k])
          break;
	else 
		k++;
}
//printf("%d ",j);
if(sub_str[j]=='\n')
     {
		 printf("match at %dth",i+1);
		 break;
	 }
}
if(str[i]=='\n')
	printf("not found!\n");
return 0;
}
