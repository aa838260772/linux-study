#include "my_pthread.h"
#include <iostream>
using namespace std;
my_pthread::my_pthread():tid(-1)
{
}

my_pthread::~my_pthread()
{
}

void my_pthread::create()
{
    if(pthread_create(&tid ,NULL ,pthreadfunc ,NULL))
    {
        throw std::runtime_error("create!");
    }
}

void my_pthread::join()
{
    if(pthread_join(tid ,NULL))
    {
        throw std::runtime_error("join!");
    }
}

void* my_pthread::pthreadfunc(void *arg)
{
    int a = 1;
    while(1)
    {
        a++;
        cout << a << endl;
        sleep(1);
    }
}




