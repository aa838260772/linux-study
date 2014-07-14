//使用封装成类的线程
#include "my_pthread.h"
#include <iostream>

using namespace std;

int main(int argc, const char *argv[])
{
    my_pthread t;
    t.create();
    t.join();
    return 0;
}
