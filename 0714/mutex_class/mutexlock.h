#ifndef _MUTEXLOCK_H_
#define _MUTEXLOCK_H_

#include <pthread.h>
#include <stdexcept>
class mutexlock{
    private:
        pthread_mutex_t lock_;
    public:
        mutexlock()  
        {
            if(pthread_mutex_init(&lock_ ,NULL))
            {
                throw std::runtime_error("init!");
            }
        }

        void lock() 
        {
            if(pthread_mutex_lock(&lock_))
            {
                throw std::runtime_error("lock!");
            }
        }

        void unlock()
        {
            if(pthread_mutex_unlock(&lock_))
            {
                throw std::runtime_error("ublock");
            }
        }


        ~mutexlock()
        {
            if(pthread_mutex_destroy(&lock_))
            {
                throw std::runtime_error("destroy");
            }
        }
};
#endif
