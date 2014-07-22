#include <iostream>
#include <string>
using namespace std;

class Person{
    public:
        Person()
            :id_(-1), name_(""), age_(0){
            };
        Person(int id, const string &name, int age)
            :id_(id), name_(name), age_(age){
            }
        void print(){
            cout << "id=" << id_ 
                << " name=" << name_ 
                << " age=" << age_ <<endl;    
        }

        void ptest()//调用基类的函数
        {
            cout << "person" << endl;
        }

        void prin()
        {
            cout <<"base" << endl;
        }

    protected:
        int id_;
        string name_;
        int age_;
};

class Student:public  Person
{
    public:
        Student(int id , string name ,
                int age ,int score = 0)
            :Person(id ,name ,age) ,score_(score)
        {}

        void print()
        {
            cout << "id= " << id_ 
                << " name= " <<name_ 
                <<" age=" <<age_ 
                <<" score=" << score_ << endl;
        }
    
        void prin()
        {
            cout << "derive "  <<endl;
        }

    private:
        int score_;
};

int main(int argc, const char *argv[])
{
    Student stu(1 ,"lily" ,19 ,99);
    stu.ptest();
    stu.Person::prin();
    stu.prin();
 
  Person *pe ;
  pe = &stu;
  pe->prin();
cout << "--------------------------" << endl;
    Student stu2(2 ,"dd" ,11 ,99);
    stu2 = stu;
    
        
    Person per(3 ,"ss" ,27);
    per.print();
    per = stu2;
    per.print();

    cout << "person:" << sizeof(Person) << endl;
    cout << "student:" << sizeof(Student) << endl;

    Person *per1;//基类指针指向派生类
    per1 = &stu;
}
