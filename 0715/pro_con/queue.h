#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <assert.h>
#include <cstddef>

class node{
    private:
        int data_;
        node* next_;
    public:
        friend class queue;
};

typedef node* nodeptr;

class queue{
    public:
        queue():front_(NULL) ,tail_(NULL) ,size_(0)
    {
    };
        ~queue()
        {
            clear();
        };
        void push(int );
        void pop();
        int top();
        bool isempty() const;
        void clear();
        size_t getsize() const;
    private:
        nodeptr front_;
        nodeptr tail_;
        size_t size_;
};

#endif
