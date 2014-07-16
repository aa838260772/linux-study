#ifndef _CON_H_
#define _CON_H_

#include <pthread.h>

class buff;

class con{

    public:
        con(buff &buf);
        void start() ;
        static void *pthreadfunc(void* arg);
        void run();
        void join();
    private:
        pthread_t tid_;
        buff &buf_;
};
#endif
