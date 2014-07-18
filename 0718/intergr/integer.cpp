#include "integer.h"

integer &integer::operator++()
{
    ++data_;
    return *this;
}

integer integer::operator++(int)
{
    integer ret(data_);
    data_++;
    return ret;
}

std::istream &operator>>(std::istream &is ,integer &data)
{
    is >> data.data_;
    return is;
}

std::ostream &operator<<(std::ostream &os ,const integer &data)
{
    os << data.data_;
    return os;
}
