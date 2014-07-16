#ifndef _BUFF_H_
#define _BUFF_H_

#include "queue.h"
#include "mutexlock.h"
#include "cond.h"

class buff
{
    public:
        buff(size_t size);
        ~buff() {}
        bool isempty() const ;
        bool isfull() const;
        void buffpro(int data);
        int buffcon();
    private:
        queue Q;
        mutable  mutexlock lock_;
        cond full_;
        cond empty_;
        size_t size_;
};

#endif
