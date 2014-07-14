#include "mutexlock.h"
#include <iostream>
using namespace std;

int main(int argc, const char *argv[])
{
   mutexlock lock1;
  
   lock1.lock();

   cout << "lock1" << endl;
  
   lock1.unlock();
 
   lock1.lock();

   cout << "lock2" << endl;
   lock1.unlock();
}
