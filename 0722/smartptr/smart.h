#ifndef _SMART_PTR_
#define _SMART_PTR_
#include <iostream>

template <typename T>
class SmartPtr
{
    public:
        explicit SmartPtr(T *ptr = NULL)
            :ptr_(ptr)
        {
            std::cout << "smartptr construct" << std::endl;
        }

        ~SmartPtr()
        {
            std::cout << "smartptr destructor" << std::endl;
            delete ptr_;
        }
        T &operator*();
        const T &operator*() const;
        T *operator->();
        const T *operator->() const;
    private:
        SmartPtr(const SmartPtr &);
        SmartPtr &operator=(const SmartPtr &);
        T *ptr_;
};

template <typename T>
    inline 
T &SmartPtr<T>::operator*()
{
    return *ptr_;
}

template <typename T>
inline 
const T &SmartPtr<T>::operator*() const
{
    return *ptr_;
}

template <typename T>
    inline
T *SmartPtr<T>::operator->()
{
    return ptr_;
}

template <typename T>
inline
const T *SmartPtr<T>::operator->() const
{
    return ptr_;
}

#endif /*SMART_PTR*/ 
