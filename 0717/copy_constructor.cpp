#include <iostream>
#include <string>

using namespace std;
class people
{
    public:
        people():name_("") ,age_(0){}

        people(const string& name ,int age)
            :name_(name) ,age_(age)
        {
            cout << "constructor" << endl;
        }

        people(const people& other)
        {
            cout << "copy constructor" << endl;
            name_ = other.name_;
            age_ = other.age_;
        }

        people &operator =(const people& other)
        {
            cout << "= constructor" << endl;
            name_ = other.name_;
            age_ = other.age_;
        }
        void  prin()
        {
            cout << name_  << " " << age_ << endl;
        }

    private:
        string name_;
        int age_;
};

int main(int argc, const char *argv[])
{
    people s1("lyli" ,23);
    s1.prin();
   
    people s2(s1);
    s2.prin();

    people s3;//不能声明时赋值，否则会调用复制构造函数 
    s3 = s1;
    s3.prin();
    return 0;
}
