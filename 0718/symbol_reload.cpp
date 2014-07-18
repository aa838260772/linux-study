//声明成员函数和友元函数两种方式实现 < 的重载
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Person{
    public:
        Person()
            :id_(-1), name_(""), age_(0){
            }

        Person(int id, const string &name, int age)
            :id_(id), name_(name), age_(age){
            }
        friend   bool operator<(const Person &the ,const Person &other);

        /*        bool operator<(const Person &other) const
                  {
                  return id_ > other.id_;
                  }
                  */
        void print(){
            cout << "id=" <<  id_ << " name=" << name_ << " age=" << age_ <<endl;    
        }
    private:
        int id_;
        string name_;
        int age_;
};

bool operator<(const Person &the ,const Person &other)
{
    return the.id_ > other.id_;
}

int main(int argc, const char *argv[])
{
    vector<Person> vec;
    vec.push_back(Person(1 ,"zhangsan" ,34));
    vec.push_back(Person(2 ,"lisi" ,33));
    vec.push_back(Person(3 ,"wangwu" ,39));


    sort(vec.begin() ,vec.end());
    for(vector<Person>::iterator it = vec.begin(); it != vec.end(); ++it){
        (*it).print();
    }
}

