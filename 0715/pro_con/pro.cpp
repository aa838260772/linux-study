#include "pro.h"
#include "buff.h"
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

pro::pro(buff& buf):tid_(0) ,buf_(buf)
{
    ::srand(1111);
}

void pro::start()
{
    pthread_create(&tid_ ,NULL ,pthreadfunc ,this);
}

void* pro::pthreadfunc(void* arg)
{
    pro *pt = static_cast<pro *>(arg);
    pt -> run();
    return NULL;    
}

void pro::run()
{
    while(1)
    {
        int data = rand()%200;
        buf_.buffpro(data);
        sleep(4);
    }
}

void pro::join() 
{
    pthread_join(tid_ ,NULL);
}
