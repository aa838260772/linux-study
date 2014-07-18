#include "complex.h"

using namespace std;

int main(int argc, const char *argv[])
{
    Complex a(2 ,3);
    cout << a;
    cout << endl;

     Complex  b;
     cin >> b;
     cout << b;
     cout << endl;

     cout << a+b;
     cout << endl;

     cout << a-b;
     cout << endl;

     cout << a*b;
     cout << endl;
    return 0;
}
