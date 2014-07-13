/*************************************************************************
  > File Name: pro_consu.c
  > Author: One
  > Mail:838260772@qq.com 
  > Created Time: 2014年07月01日 星期二 14时12分40秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include<stdlib.h>
#define N 10
int queue[N];
int front =-1;
int tail=0;
int pro_num=0;
int left_num=N;
pthread_mutex_t mymutex;//实现互斥对缓冲区的操作
pthread_cond_t produce,consumer;//生产条件，消费条件
static void* pro_func(void*);
static void* con_func(void*);
int main(int argc,char *argv[])
{
	srand(getpid());

	pthread_t tid1,tid2;
	pthread_mutex_init(&mymutex,NULL);//初始化
	pthread_cond_init(&produce,NULL);
	pthread_cond_init(&consumer,NULL);

	int p1=atoi(argv[1]);
	int p2=atoi(argv[2]);

	while(p1)
	{
		pthread_create(&tid1,NULL,pro_func,NULL);
		p1--;
	}	
	while(p2)
	{
		pthread_create(&tid2,NULL,con_func,NULL);
		p2--;
	}

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

	pthread_mutex_destroy(&mymutex);
	pthread_cond_destroy(&produce);
	pthread_cond_destroy(&consumer);
	return 0;
}

void* pro_func(void *arg)
{
	while(1)
	{
		pthread_mutex_lock(&mymutex);
		while(left_num==0)
			pthread_cond_wait(&produce,&mymutex);
		pro_num++;
		left_num--;
		queue[tail]=rand()%100;
		printf("producer: tail:%d  pro_num:%d\n",queue[tail],pro_num);
		tail++;
		if(pro_num==1)//商品数量为1时就通知消费者可以消费了
			pthread_cond_broadcast(&consumer);
		pthread_mutex_unlock(&mymutex);
		sleep(rand()%5+1);
	}
}

void* con_func(void *arg)
{
	while(1)
	{
		pthread_mutex_lock(&mymutex);
		while(pro_num==0)//当唤醒队列用pthread_cond_broadcast时此处要用while
			pthread_cond_wait(&consumer,&mymutex);
		pro_num--;
		left_num++;
		printf("consumer: tail:%d  pro_num: %d\n",queue[tail-1],pro_num);
		tail--;
		if(left_num==1)//缓冲区有空位，通知生产者可以生产了
			pthread_cond_broadcast(&produce);
		pthread_mutex_unlock(&mymutex);
		sleep(rand()%5+1);
	}
}










