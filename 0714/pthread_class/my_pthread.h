//将线程封装成类:
#ifndef _MY_PTHREAD_H_
#define _MY_PTHREAD_H_

#include <pthread.h>
#include <stdexcept>
#include <unistd.h>
class my_pthread{
    public:
        my_pthread();
        ~my_pthread();
       void create();
     static void *pthreadfunc(void* arg);//此函数是作为pthread_creat调用的，需声明为static
       void join();
    private:
       pthread_t tid;
};
#endif
