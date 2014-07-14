#ifndef _QUEUE_H_       
#define _QUEUE_H_
#include <iostream>
#include <assert.h>
#include <stdlib.h>

class node{
    friend class queue;
    private:
        int data;
        node* next;
};

typedef  node* nodePtr;
class queue{
   private:
          nodePtr front;
          nodePtr tail;
          size_t size;
   public:
       queue();
       ~queue();
       void init();
       void clear();
       void push(int);
       void pop();
       int top() const;
       bool isempty() const;
      size_t getsize() const;  
};

#endif
