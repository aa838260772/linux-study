#ifndef _PTHREAD_H_
#define _PTHREAD_H_ 

#include "my_queue.h"
#include <pthread.h>

//定义线程池结构体
typedef struct
{
 size_t size_;
 pthread_t *pthreads_;//线程数组指针
 BOOL is_started_;
 queue queue_;//任务队列
 pthread_mutex_t mutex_;
 pthread_cond_t cond_;
}pool_t;

void thread_pool_init(pool_t *, size_t size);
void thread_pool_destroy(poll_t *);
void thread_pool_start(pool_t);
void thread_pool_stop(pool_t *, task_t);
void thread_pool_add_task_queue(pool_t *, task_t);
BOOL thread_pool_get_task_from_queue(pool *, task_t *);
BOOL thread_pool_is_started(const pool_t *);
size_t thread_pool_get_size_of_queue(const pool_t *);

#endif /*PTHREAD_H*/ 
