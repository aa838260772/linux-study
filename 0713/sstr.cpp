#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

int main(int argc, const char *argv[])
{
    ostringstream oss;
    oss << "hello" << 1 << " " << "world";
    string s;
    int a = 33;
    istringstream iss(oss.str());
   
   cout << oss.str() <<endl;
    iss >> s >> a;
    cout << s << " " << a <<endl;
    return 0;
}

