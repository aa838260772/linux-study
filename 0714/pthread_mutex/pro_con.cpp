#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include "queue.h"
#define MAXSIZE 5
using namespace std;

pthread_mutex_t mutex;//互斥锁
pthread_cond_t  full;//满条件
pthread_cond_t empty;//空条件
queue Q;

void *producer(void *arg)
{
    int s;
    while(1)
    {
        pthread_mutex_lock(&mutex);
        while(Q.getsize() == MAXSIZE)
            pthread_cond_wait(&empty ,&mutex );
        s = rand()%100;
        Q.push(s);
        cout << "produce a nunber:" << s <<  "  "  << pthread_self()<< endl;
       
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);
    }
}

void *consumer(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        while(Q.isempty())//这里用if的时候出现了问题，
            pthread_cond_wait(&full ,&mutex);
        cout << "consum  a nunber:" << Q.top() <<  "  "  << pthread_self() << endl;
        Q.pop();
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, const char *argv[])
{
    srand(time(NULL));
    pthread_mutex_init(&mutex ,NULL);
    pthread_cond_init(&full ,NULL);
    pthread_cond_init(&empty ,NULL);

    int i = 4;
    pthread_t tid;
    while(i)//创建所有生产者线程
    {
    pthread_create(&tid ,NULL , producer ,NULL);
    pthread_detach(tid);
    i--;
    }

    i = 3;
   while(i)//消费者线程
   {
   pthread_create(&tid ,NULL ,consumer ,NULL);
    pthread_detach(tid);
   i--;
   }
   
   while(1);
     pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);
    pthread_mutex_destroy(&mutex);

    return 0;
}






