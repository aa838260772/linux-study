#include <iostream>
#include "smart.h"

using namespace std;

class test
{
    public:
        test()
        {
        cout << "test construct" << endl;
        }

        ~test()
        {
        cout << "test destructor" << endl;
        }
};

int main(int argc, const char *argv[])
{  
   SmartPtr<test> ptr;
   test *p = new test ;
   delete p;
   cout << "-------------------------------" << endl;
}
