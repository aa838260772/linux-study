/*************************************************************************
	> File Name: mythread_lock.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月30日 星期一 16时51分16秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#define N 1000
pthread_mutex_t  mymutex;
int cnt=0;
static void* handler(void *);
int main()
{
pthread_t tid1,tid2;
pthread_mutex_init(&mymutex,NULL);
pthread_create(&tid1,NULL,handler,NULL);
pthread_create(&tid2,NULL,handler,NULL);
pthread_mutex_destroy(&mymutex);
pthread_join(tid1,NULL);
pthread_join(tid2,NULL);

printf("the res is:%d\n",cnt);
return 0;
}

void* handler(void * arg)
{
int i=0;
for(i=0;i<N;++i)
{
pthread_mutex_lock(&mymutex);
cnt++;
printf("tid : %u\n",pthread_self());
sleep(1);
pthread_mutex_unlock(&mymutex);
}

}

