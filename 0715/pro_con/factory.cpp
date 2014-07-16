#include "factory.h"
using namespace std;

factory::factory(size_t bufsize,
        size_t pronum,
        size_t connum)
:bufsize_(bufsize) ,
    buf_(bufsize_),
    pronum_(pronum),
    connum_(connum),
    pro_(pronum_ ,pro(buf_)),
    con_(connum_ ,con(buf_))
{
}

void factory::start()
{
    for(vector<pro>::iterator it = pro_.begin() ; it != pro_.end() ;it++)
    {
        it -> start();
    }

    for(vector<con>::iterator it = con_.begin() ; it != con_.end() ;it++)
    {
        it -> start();
    }

    for(vector<pro>::iterator it = pro_.begin() ; it != pro_.end() ;it++)
    {
        it -> join();
    }


    for(vector<con>::iterator it = con_.begin() ; it != con_.end() ;it++)
    {
        it -> join();
    }
}
