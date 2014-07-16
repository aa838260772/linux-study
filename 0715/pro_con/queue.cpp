#include "queue.h"

void queue::push(int data)
{
    nodeptr pt = new node;
    pt -> data_ = data;
    pt -> next_ = NULL;
    if(front_ == NULL)
    {
        front_ = tail_ = pt;
    }else
    {
        tail_ -> next_ = pt;
        tail_ = pt;
    }
    size_++;
}

void queue::pop()
{
    nodeptr pt;
    assert(!isempty());
    pt = front_;
    front_ = front_ -> next_;
    delete(pt);
    size_--;
}

int queue::top()
{
    assert(!isempty());
    return (front_ -> data_);
}

bool queue::isempty() const
{
    return front_ == NULL;
}

void queue::clear()
{
    while(!isempty())
        pop();
}
size_t queue::getsize() const
{
    return size_;
}


