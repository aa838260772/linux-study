#ifndef _PRO_H_
#define _PRO_H_

#include <pthread.h>

class buff;

class pro{

    public:
        pro(buff &buf);
        void start() ;
        static void *pthreadfunc(void* arg);
        void run();
        void join();
    private:
        pthread_t tid_;
        buff &buf_;
};
#endif
