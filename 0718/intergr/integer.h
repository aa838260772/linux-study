#ifndef _INTEGER_H_
#define _INTEGER_H_
#include <iostream>

class integer
{
    friend std::istream &operator>>(std::istream & ,integer &) ;
    friend std::ostream &operator<<(std::ostream & ,const integer &);
    public:
      integer():data_(0)
    {}
    explicit integer(int data)   
        :data_(data)
    {}
    ~integer()
    {}

    integer &operator++();
    integer  operator++(int);//输出的时候i++(后缀) 输出的不是i的值，而是一个临时变量
    private:
    int data_;
};
#endif /*INTEGER_H*/ 

