#ifndef _MUTEX_H_
#define _MUTEX_H_

#include <pthread.h>
#include <stdexcept>

class mutexlock{
    public:
        mutexlock()
        {
            if(pthread_mutex_init(&mutex ,NULL))
                throw std::runtime_error("pthread_mutex_init!");
        }
        ~mutexlock()
        {
            if(pthread_mutex_destroy(&mutex ))
                throw std::runtime_error("pthread_mutex_destroy!");
        }
        void lock()
        {
            if(pthread_mutex_lock(&mutex))
                throw std::runtime_error("pthread_mutex_lock!");
        }

        void unlock()
        {
            if(pthread_mutex_unlock(&mutex ))
                throw std::runtime_error("pthread_mutex_unlock!");
        }
       
        pthread_mutex_t* getmutex()
        {
        return &mutex;
        }
    private:
        pthread_mutex_t mutex;
};
#endif
