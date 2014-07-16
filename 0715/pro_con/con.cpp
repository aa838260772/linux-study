#include "con.h"
#include "buff.h"
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

con::con(buff& buf):tid_(0) ,buf_(buf)
{
}

void con::start()
{
    pthread_create(&tid_ ,NULL ,pthreadfunc ,this);
}

void* con::pthreadfunc(void* arg)
{
    con *pt = static_cast<con *>(arg);
    pt -> run();
    return NULL;    
}

void con::run()
{
    while(1)
    {
         buf_.buffcon();
        
        sleep(1);
    }
}

void con::join() 
{
    pthread_join(tid_ ,NULL);
}


