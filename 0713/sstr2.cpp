#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

int main(int argc, const char *argv[])
{
    int a=33;
   ostringstream oss;
   oss << "hello";
   istringstream iss(oss.str());
   iss >> a;
   cout << a << endl;
    return 0;
}
