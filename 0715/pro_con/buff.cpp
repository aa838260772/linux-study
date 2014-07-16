#include "buff.h"
#include <iostream>
using namespace std;

buff::buff(size_t size):
    Q(),
    lock_(),
    full_(lock_),
    empty_(lock_),
    size_(size)
{
}

bool buff::isempty() const
{
    lock_.lock();
    bool ret = Q.isempty();
    lock_.unlock();

    return ret;
}

bool buff::isfull() const
{
    lock_.lock();
    bool ret = (Q.getsize() >= size_);
    lock_.unlock();

    return ret;
}

void buff::buffpro(int data)
{
    lock_.lock();
    while(Q.isempty()>= size_ )
    {
        empty_.wait();
    }
    Q.push(data);
    cout << "produce a data" << data << endl;
    cout << "product size" << Q.getsize() << endl;
    full_.notify();
    lock_.unlock();
}

int buff::buffcon()
{
    lock_.lock();
    while(Q.isempty())
    {
        full_.wait();
    }

    int ret = Q.top();
    Q.pop();
    cout << "consume a date:" << ret << endl;
    cout << "product size :" << Q.getsize() << endl;
    empty_.notify();
    lock_.unlock();

    return ret;
}












