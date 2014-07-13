/*************************************************************************
	> File Name: pro.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月23日 星期一 18时47分38秒
 ************************************************************************/

#include "pro.h"
static int partion(word *[],int);
static void get_next(char *);
int next[30];
void text_process(int a,int b,int *line_num,int *total_char)
{
char *c;
c=(char*)malloc(sizeof(char));
int cnt,sign=1;
while((cnt=read(a,c,1))!=0)
{
	if(*c=='\r')
		(*line_num)++;
if(ispunct(*c)||*c=='\t')
	*c=' ';
else if(*c!=' '){
   if(*c>='A'&&*c<='Z')
     *c=*c+32;
   sign=1;
    }
if(sign==1||*c!=' ')
   write(b,c,1);
if(*c==' ')
	sign=0;
(*total_char)++;
}
}

void rd_in(word *a[],FILE *fp,int *word_dif,int *word_count)
{
int i;
char str[20];
word *p;
while(memset(str,0,20),fscanf(fp,"%s",str)!=EOF)
{
for(i=0;i<*word_dif;i++)
{
   if(strcmp(a[i]->name,str)==0)
	   break;
 }
if(i==*word_dif)
{
(*word_dif)++;
p=(word*)calloc(1,sizeof(word));
strcpy(p->name,str);
p->count=1;
a[i]=p;
}else
{
a[i]->count++;
}
(*word_count)++;
}
}

int partion(word *a[],int len)
{
int low=0,high=len-1;
word *p;
p=a[low];
while(low<high)
{
while(low<high&&a[high]->count<p->count)
             high--;
if(low<high)
      a[low]=a[high];
while(low<high&&a[low]->count>=p->count)
        low++;
if(low<high)
	a[high]=a[low];
}
a[low]=p;
return low;
}

void quick_sort(word *a[],int len)
{
int  pri; 
if(len>1)
{
pri=partion(a,len);
quick_sort(a,pri);
quick_sort(a+pri+1,len-pri-1);
}
}

void get_next(char *str)
{
int i=0,j=-1;
next[0]=-1;
while(i!=strlen(str))
{
if(j==-1||str[i]==str[j])
{
++i;
++j;
if(str[i]==str[j])
	next[i]=next[j];
else
	 next[i]=j;
}
else
     j=next[j];
}
}

int index_kmp(char *str,char *sub)
{
get_next(sub);
int i,j;
i=0,j=0;
while(i!=strlen(str)&&j!=strlen(sub))
{
if(j==-1||str[i]==sub[j])
{
i++;
j++;
}
else
j=next[j];
}
if(j==strlen(sub))
	return i-j+1;
else
	return 0;

}

void line_pro(char *line[],FILE *fp)
{
char str[MAX_LEN];
char *p;
int i=0;
while(memset(str,0,MAX_LEN),fgets(str,MAX_LEN,fp)!=NULL)
{
p=(char *)calloc(1,strlen(str)*sizeof(char)+1);
strcpy(p,str);
line[i]=p;
i++;
}
}

void search_sub(char *line[],char *sub,int line_num)
{
int sign=0; 
char str[MAX_LEN];
int i=0,count=0;
while(i<=line_num)
{
if(index_kmp(line[i],sub))
{
count++;
puts(line[i]);
sign=1;
}
i++;
}
if(sign==1)
printf("%s occurs in %d lines\n",sub,count);
else
 printf("%s not occur!\n");
}

void pro_space(char *str)
{
int i=0,j=0;
int sign=1;
while(str[i]!='\n')
{
if(str[i]!=' ')
{
	str[j++]=str[i];
    sign=1;
}
else if(sign==1) 
{
str[j++]=str[i];
sign=0;
}
i++;
}
str[i]='\0';
}

