//定义队列结构体,用以存储任务
#ifndef _QUEUE_
#define _QUEUE_

#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef int BOOL;
#define TRUE 1
#define FALSE 0 
typedef struct
{
void (*thread_callback)(void*);
void *arg;
}task_t;

typedef struct q_node
{
 task_t data_;
struct q_node *next;
}q_node, *p_node;

typedef struct
{
 p_node head_;
 p_node tail_;
 size_t size_;
}queue;

void queue_init(queue *);
void queue_destroy(queue *);
void queue_push(queue*, task_t);
void quque_pop(queue*);
void queue_clear(queue*);
task_t queue_top(const queue *) ;
BOOL queue_empty(const queue *);
size_t queue_getsize(const queue *);

#endif /*QUEUE*/ 
