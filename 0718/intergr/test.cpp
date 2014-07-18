#include "integer.h"

using namespace std;

int main(int argc, const char *argv[])
{
     integer a(3);
     
     cout << a;
     cout << a++ ;

     cout << endl;
     cout << ++a;
     cout << endl;

     integer b;
     cin >> b;
     cout << b;
    return 0;
}
