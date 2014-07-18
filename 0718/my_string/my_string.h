#ifndef __MY_STRING_
#define __MY_STRING_

#include <iostream>
#include <string.h>
//#include  <stddef.h>

class String
{
    friend std::ostream &operator<<(std::ostream &, const String &);
    friend std::istream &operator>>(std::istream & ,String &);

    friend String operator+(const String & ,const String &);
    friend String operator+(const String & ,const char *);
    friend String operator+(const char * ,const String &);

    friend bool operator<(const String & ,const String &);
    friend bool operator>(const String & ,const String &);
    friend bool operator<=(const String & ,const String &);
    friend bool operator>=(const String & ,const String &);
    friend bool operator==(const String & ,const String &);
    friend bool operator!=(const String & ,const String &);

    public:
    String();
    String(const char *);
    String(const String&);
    ~String();

    String &operator=(const char*);
    String &operator=(const String&);

    String &operator+=(const char *);
    String &operator+=(const String&);//返回引用是为了连续赋值

    char &operator[](size_t index);
    char operator[](size_t index) const;
    const char *c_str() const;
    size_t size() const;
    void debug() const;
    private:
    char *str_;
};

#endif /*_MY_STRING*/ 
