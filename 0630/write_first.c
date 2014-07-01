/*************************************************************************
	> File Name: write_first.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月30日 星期一 22时09分45秒
 ************************************************************************/

#include<stdio.h>
#include<time.h>
#include<pthread.h>
#include<stdlib.h>
int cnt=0;
int read=0;
int write=0;
pthread_mutex_t read_mutex,write_mutex,mutex;
static void* write_hander(void *);
static void* read_hander(void*);

int main()
{
int i;
pthread_t tid;
srand(getpid());
pthread_mutex_init(&read_mutex,NULL);//读期间修改cnt时不让其他的读同时修改
pthread_mutex_init(&write_mutex,NULL);//写期间值的互斥改变
pthread_mutex_init(&mutex,NULL);//有写者时不让读者进
while(1)
{
i=rand()%2;
if(i==0)
{
pthread_create(&tid,NULL,write_hander,NULL);
}
else
{
pthread_create(&tid,NULL,read_hander,NULL);
}
sleep(1);
}
pthread_mutex_destroy(&read_mutex);
pthread_mutex_destroy(&write_mutex);
pthread_mutex_destroy(&mutex);
return 0;
}

void* write_hander(void*arg)
{
pthread_detach(pthread_self());

pthread_mutex_lock(&write_mutex);//写者加1
printf("write in\n");
if(write==0)
	pthread_mutex_lock(&mutex);//关闭读的锁
write++;
printf("read: %d  write: %d \n",read,write);
pthread_mutex_unlock(&write_mutex);

pthread_mutex_lock(&write_mutex);//互斥写
cnt++;
write--;
printf("write out cnt-->%d\n",cnt);
sleep(4);
if(write==0)
	pthread_mutex_unlock(&mutex);
pthread_mutex_unlock(&write_mutex);
}

void* read_hander(void *arg)
{
pthread_detach(pthread_self());

pthread_mutex_lock(&read_mutex);
printf("read in\n");
read++;
printf("read: %d  write: %d \n",read,write);
pthread_mutex_unlock(&read_mutex);
sleep(4);

pthread_mutex_lock(&mutex);
printf("read out--->cnt:%d\n",cnt);
read--;
pthread_mutex_unlock(&mutex);
}


