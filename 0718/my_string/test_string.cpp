#include "my_string.h"
#include <iostream>

using namespace std;

int main(int argc, const char *argv[])
{
    String s1("hello");
    s1.debug();

    String s2;
    s2 = s1;
    s2.debug();
    
    String s3(s2);
    s3.debug();

    s3 += " hah";
    s3.debug();
    cout << (s1 ==  s2) << endl;
 
    String s4;
    cin >> s4;
   cout << s4;

    cout << s3[0] << endl;
    return 0;
}

