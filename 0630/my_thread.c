/*************************************************************************
	> File Name: my_thread.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月30日 星期一 20时56分41秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
static void* handler(void*);
int main()
{
pthread_t tid;
//char *p="hello world!";
char p[]="hello world";
pthread_create(&tid,NULL,handler,(void*)p);
pthread_join(tid,NULL);

return 0;
}

void* handler(void * arg)
{
char *str=(char*)arg;
printf("the string is %s\n",str);
}





