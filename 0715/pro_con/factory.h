#ifndef _FACT_H_
#define _FACT_H_
#include <vector>
#include "con.h"
#include "pro.h"
#include "buff.h"

class factory
{
    public:
         factory(size_t bufsize,
                 size_t pronum,
                 size_t connum);
         void start();
     private:
         size_t bufsize_;
         size_t pronum_;
         size_t connum_;
         buff buf_;
         std::vector<pro> pro_;
         std::vector<con> con_;
};

#endif
