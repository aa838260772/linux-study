//容器的几种初始化方法，使用迭代器模板输出元素
#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

template< typename T >
void prin(T begin ,T end)
{
  for(T pt = begin ; pt != end ; pt++)
      cout << *pt << endl;
}

int main(int argc, const char *argv[])
{
    vector<string> vec ;
    vec.push_back("hello");
    vec.push_back("world");
      cout << "vec" << endl;
    prin(vec.begin() ,vec.end());

    vector<string> vec1(vec);
      cout << "vec1" << endl;
     prin(vec1.begin() ,vec1.end());
    
     vector<string> vec2(4 , "test");
      cout << "vec2" << endl;
     prin(vec2.begin() ,vec2.end());

    vector<string> vec3(vec.begin() ,vec.end());
      cout << "vec3" << endl;
     prin(vec3.begin() ,vec3.end());

    list<string> lis(vec.begin() ,vec.end());
      cout << "list" << endl;
       prin(lis.begin() ,lis.end());
   
    vector<int> vec5(10);//vec5中有10个元素，是系统默认的初始化值
      cout << "vec5" << endl;
       prin(vec5.begin() ,vec5.end());

    return 0;
}









