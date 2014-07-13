#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;


int main(int argc, const char *argv[])
{
    while(1)
    {
     int i;
        cin>> i;
      cout << cin.good() << endl;//输入错误格式时，进入死循环，需要刷新
      cin.clear();//将流置为有效状态
      cin.ignore(numeric_limits< std::streamsize >::max() , '\n');
      cout << i << endl;
    }
    return 0;
}
