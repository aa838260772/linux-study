#ifndef _COND_H_
#define _COND_H_

#include "mutexlock.h"
#include <assert.h>
#include <stdexcept>
#include <pthread.h>

class cond{
public:
    cond(mutexlock &lock):lock_(lock)
    {
        if(pthread_cond_init(&cond_ ,NULL))
            throw std::runtime_error("pthread_cond_init!");
    }
    ~cond()
    {
        if(pthread_cond_destroy(&cond_))
            throw std::runtime_error("pthread_cond_destroy!");
    }
     void wait()
    {
        if(pthread_cond_wait(&cond_ ,lock_.getmutex()))
            throw std::runtime_error("pthread_cond_wait!");
    }

   void notify()
    {
        if(pthread_cond_signal(&cond_))
            throw std::runtime_error("pthread_cond_signal!");
    }

   void  notifyall()
    {
        if(pthread_cond_broadcast(&cond_))
            throw std::runtime_error("pthread_cond_broadcast!");
    }

    private:
    mutexlock &lock_;
    pthread_cond_t cond_;
};
#endif
