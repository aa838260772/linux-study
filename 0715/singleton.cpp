//单例模式，实现某个类只能创建ｎ个对象,多个线程抢占时会出现问题，要加个锁，并且double check
#include <iostream>

using namespace std;

class singleton
{
    private:
        singleton(){
        cout << "constructor" << endl;
        }
        static singleton *pinstance;
        static int a_;
    public:
        static singleton* GetInstance()
        {
//        if(pinstance == NULL)
            if( a_ < 3)
            {
            pinstance = new singleton;
              a_++;
            }
        return pinstance;
        }
};

singleton* singleton::pinstance = NULL;
int  singleton::a_ = 1;

int main(int argc, const char *argv[])
{
    singleton *ps = singleton::GetInstance();
    cout << ps << endl;
    singleton *ps1 = singleton::GetInstance();
    cout << ps1 << endl;
    singleton *ps2 = singleton::GetInstance();
    cout << ps2 << endl;
    singleton *ps3 = singleton::GetInstance();
    cout << ps3 << endl;
    singleton *ps4 = singleton::GetInstance();
    cout << ps4 << endl;
    singleton *ps5 = singleton::GetInstance();
    cout << ps5 << endl;
}













