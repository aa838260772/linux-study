/*************************************************************************
	> File Name: mypthread_creat.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月30日 星期一 16时19分04秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include<stdlib.h>
#define N 10000
void* handle(void *);
int main()
{
int i,a[N];
srand(time(NULL));
for(i=0;i<N;++i)
	a[i]=rand()%100;
pthread_t tid;
pthread_create(&tid,NULL,handle,(void*)a);
pthread_join(tid,NULL);

return 0;
}

void* handle(void *arg)
{
int *val=(int *)arg;
int i;
float sum=0;
for(i=0;i<N;++i)
	sum+=val[i];
printf("hello  %f \n",sum);
}

