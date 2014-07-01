/*************************************************************************
  > File Name: read_first.c
  > Author: One
  > Mail:838260772@qq.com 
  > Created Time: 2014年06月30日 星期一 21时28分31秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<time.h>
pthread_mutex_t read_mutex,write_mutex;//两个锁均是为了改变数值而设定，防止改变其间被其他改变
static void* write_handler(void *);
static void* read_handler(void *);
int read=0;
int write=0;
int cnt=0;
int main()
{
	int i;
	srand(getpid());
	pthread_mutex_init(&read_mutex,NULL);
	pthread_mutex_init(&write_mutex,NULL);
	while(1)
	{
		printf("read:%d   write:%d\n",read,write);
		pthread_t tid;
		i=rand();
		if(i%2==0)
		{
			pthread_create(&tid,NULL,write_handler,NULL);
		}else
		{
			pthread_create(&tid,NULL,read_handler,NULL);
		}
		sleep(2);
	}
	pthread_mutex_destroy(&read_mutex);
	pthread_mutex_destroy(&write_mutex);
	return 0;
}

void* write_handler(void *arg)
{
	pthread_detach(pthread_self());
	write++;

	/*pthread_mutex_lock(&write_mutex);
	printf("read: %d  write: %d\n",read,write);
	pthread_mutex_unlock(&write_mutex);
	sleep(5);
  */
	pthread_mutex_lock(&write_mutex);
	cnt++;
	write--;
	sleep(5);
	printf("after writer cnt:%d\n",cnt);
	pthread_mutex_unlock(&write_mutex);
}

void* read_handler(void *arg)
{
	pthread_detach(pthread_self());
	pthread_mutex_lock(&read_mutex);
	if(read==0)//读者优先，有读者在时不让写者进，
	{
		pthread_mutex_lock(&write_mutex);//有读者的时候不让写者进
	}
	pthread_mutex_unlock(&read_mutex);

	pthread_mutex_lock(&read_mutex);
	read++;
	pthread_mutex_unlock(&read_mutex);
	//printf("read: %d  write: %d\n",read,write);
	printf("read in,cnt:%d\n",cnt);
	sleep(5);
	pthread_mutex_lock(&read_mutex);
		read--;
	//printf("read in,cnt:%d\n",cnt);
	if(read==0)
		pthread_mutex_unlock(&write_mutex);
	pthread_mutex_unlock(&read_mutex);

}










