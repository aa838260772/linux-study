/*************************************************************************
	> File Name: main.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月23日 星期一 19时32分04秒
 ************************************************************************/

#include <stdio.h>
#include "pro.h"
word *a[1000000];
int main(int argc,char **argv)
{
int fd_src,fd_des;
int line_num=0,word_dif=0,word_cnt=0,total_char=0;
int i;
char *line[MAX_LINE_LEN];
char str[30];
char input[30];
fd_src=open(argv[1],O_RDONLY);
fd_des=open(argv[2],O_RDWR|O_CREAT,0666);
text_process(fd_src,fd_des,&line_num,&total_char);
//printf("%d\n",line_num);
close(fd_src);
close(fd_des);

FILE *fp;
fp=fopen(argv[2],"r");
rd_in(a,fp,&word_dif,&word_cnt);
//printf("%d    %d",word_dif,word_cnt);
quick_sort(a,word_dif);
/*for(i=0;i<10;++i)
{
printf("%s  %d\n",a[i]->name,a[i]->count);
}
	str[i]='\0';
*/
rewind(fp);
line_pro(line,fp);
char s1[15];
char s2[15];
printf("init success!\n");
while(memset(input,0,sizeof(input)),fgets(input,sizeof(input),stdin))
{
memset(s1,0,15);
memset(s2,0,15);
pro_space(input);
sscanf(input,"%s %s",s1,s2);//把input分解成命令和操作参数
if(strcmp(s1,"wc")==0)
{
switch(s2[1])
{
	case 'l': printf("there are %d lines!\n",line_num);
             break;
	case 'c':printf("there are %d chars!\n",total_char);
              break;
	case 'w':printf("there are %d words!\n",word_cnt);
			 break;
   default:break;
}
}
else if(strcmp(s1,"find")==0)
{
search_sub(line,s2,line_num);
}

else if(strcmp(s1,"top")==0)
{
int k=atoi(s2);
for(i=0;i<k;++i)
printf("%-10s  %-10d\n",a[i]->name,a[i]->count);
}
else
 printf("false\n");
}
fclose(fp);
	return 0;
}


