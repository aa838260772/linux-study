#include "complex.h"
#include <iostream>

std::istream &operator>>(std::istream &in ,Complex &com)
{
    in >> com.int_ >> com.complex_;
    return in;
}

std::ostream &operator<<(std::ostream &os ,const Complex &com)
{
    if(com.complex_ < 0)
    os << com.int_  << com.complex_ <<"i";
    else
    os << com.int_ << "+" << com.complex_ <<"i";
    return os;
}

Complex Complex::operator+(const Complex &com)
{
    Complex a;
    a.int_ = int_ + com.int_;
    a.complex_ = complex_ + com.complex_;
    return  a;
}

Complex Complex::operator-(const Complex &com)
{
    Complex a;
    a.int_ = int_ - com.int_;
    a.complex_ = complex_ - com.complex_;
    return  a;
}

Complex Complex::operator*(const Complex &com)
{
    Complex a;
    a.int_ = (int_ * com.int_) - (complex_ * com.complex_);
    a.complex_ =  (int_ * com.complex_) + (complex_ * com.int_);
    return  a;
}

/*Complex Complex::operator/(const Complex com)
{
    Complex a;
    int_ += com.int_;
    complex_ += com.complex_;
    return  a;
}
*/
