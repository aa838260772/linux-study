#include "my_pthread.h"

void thread_init(pool_t *pool, size_t size);
{
    pool->size_ = size;
    pool->pthreads = (pthread_t*)caloc(size, sizeof pthread_t);
    pool->is_started_ = FALSE;
    queue_init(&(pool->queue_));
    pthread_mutex_init(&pool->mutex_, NULL);
    pthread_cond_init(&pool->cond_, NULL);
}
