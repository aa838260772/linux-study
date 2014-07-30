#include "my_queue.h"

void queue_init(queue *Q)
{
    Q->head_ = Q->tail_ = NULL;
    Q->size_ = 0;
}

void queue_pop(queue *Q)
{
    assert(!queue_empty(Q));
    p_node p = Q->head_;
    Q->head_ = Q->head_->next;
    free(p);
    --Q->size_;
}

void queue_destroy(queue *Q)
{
    while(!queue_empty(Q))
    {
        queue_pop(Q);
    }
}

void queue_push(queue *Q, task_t tas)
{
    p_node p;
    p = (p_node)malloc(sizeof(q_node));
    p->data_ = tas;
    p->next = NULL;

    if(queue_empty(Q))
    {
        Q->head_ = Q->tail_ = p;
    }else
    {
        Q->tail_->next= p;
        Q->tail_ = p; 
    }
    ++Q->size_;
}


task_t queue_top(const queue *Q)
{
    assert(!queue_empty(Q));
    return Q->head_->data_;
}

BOOL queue_empty(const queue *Q)
{
    return (Q->head_ == NULL);
}

size_t queue_getsize(const queue *Q)
{
    return Q->size_;
}


