#ifndef _COMPLEX_H_
#define _COMPLEX_H_

#include <iostream>
class Complex
{

    friend std::istream &operator>>(std::istream &in ,Complex &);
    friend std::ostream &operator<<(std::ostream &os ,const Complex &);
    public:
        Complex()
            :int_(0) ,complex_(0)
        {}
        Complex(int data1 ,int data2)
            :int_(data1) ,complex_(data2)
        {}
        Complex operator+(const Complex &com);
        Complex operator-(const Complex &com);
        Complex operator*(const Complex &com);
       // Complex operator/(const Complex &com);
    private:
        int int_;
        int complex_;
};
#endif /*COMPLEX_H*/ 
