//程序实现将队列封装成类，然后通过类的方法调用
#include "queue.h"
using namespace std;

int main(int argc, const char *argv[])
{
    queue Q;
    Q.push(3);
   cout<< Q.top() << endl;
    return 0;
}
