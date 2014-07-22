#include "animal.h"
#include "handle.h"

handle::handle()
    :ptr_(NULL)
{
}

handle::handle(const animal &a)
    :ptr_(a.copy())
{
}

 handle::handle(const handle &other)
    :ptr_(other.ptr_->copy())
{
}

handle::~handle()
{
    delete ptr_;
}

handle &handle::operator=(const handle &other)
{
    if(this != &other)
    {
        delete ptr_;
        ptr_ = other.ptr_->copy();
    }
    return *this;
}

animal *handle::operator->()
{
    return ptr_;
}

const animal *handle::operator->() const
{
    return ptr_;
}
