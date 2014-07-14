//构造函数，复制构造函数
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class student{
    private:
        string _name;
        int _age;
        int _score;
    public:
        student(const student&  pre):
            _name(pre._name),
            _age(pre._age),
            _score(pre._score)
    {
        cout << "constractor1" <<endl;
    }
        student(const string& name ,
                int age ,
                int score)
            :_name(name) ,_age(age) ,_score(score)
        {
            cout << "constructor2" << endl;
        }
        student& ret()
        {
            return *this;
        }

        void prin()
        {
            cout << this ->_name 
                << " " 
                << this -> _age 
                << " " 
                << this ->_score <<endl;
        }
        ~student()
        {
            cout << "deconstructor" <<endl;
        }
};

int main(int argc, const char *argv[])
{
    student s1("lily" ,23 ,98);
    student s2( s1.ret());
    student s3(s1);
    (s1.ret()).prin();
    s2.prin();
}
