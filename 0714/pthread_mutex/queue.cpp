#include "queue.h"

queue::queue():front(NULL) ,tail(NULL) ,size(0)
{
}

queue::~queue()
{
}

void queue::init()
{
    front = tail = NULL;
    size = 0;
}

void queue::push(int dat)
{
    nodePtr pt = new node;
    pt -> next = NULL;
    pt -> data =dat;

    if(isempty())
    {
        front = tail = pt;
    }else
    {
        tail -> next = pt;
        tail = pt;
    }
    size++;
}

void queue::pop()
{
    nodePtr pt;
    assert(!isempty());
    pt = front;
    front = front -> next;
    delete pt;
    size--;
}

void  queue::clear()
{
    while(!isempty())
        pop();
}

int queue::top() const
{
    assert(!isempty());
    return front -> data;
}

bool queue::isempty() const
{
    return front == NULL;
}

size_t queue::getsize() const
{
    return size;
}

