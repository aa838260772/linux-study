#include <iostream>
#include <string>
#include <vector>

using namespace std;


void prin(vector<string> &vec)
{
    for(vector<string>::iterator iter = vec.begin() ; iter != vec.end() ;iter++)
        cout << *iter << endl;
}

int main(int argc, const char *argv[])
{

    vector<string> vec;
    vec.push_back("h1");
    vec.push_back("h2");
    vec.push_back("h3");
    vec.push_back("h4");
    vec.push_back("h5");
    vec.push_back("h6");
    cout << "-----push_back--------" << endl;
    prin(vec);
    cout << "------pop_back---------" << endl;//pop vector尾部元素
    vec.pop_back();
    prin(vec);
    cout << "-------insert-------------" << endl;//在头部和尾部插入元素
    vec.insert(vec.begin() ,"h7");
    vec.insert(vec.begin() ,"h8");
    vec.insert(vec.begin() ,"h9");
    vec.insert(vec.end() ,"h10");
    prin(vec);
    cout << "-------erase----------------" << endl;//删除，erase，
    vector<string>::iterator iter = vec.begin()+3;
    vec.erase(iter);//在list中时如果是这种操作就会导致迭代器失效
    prin(vec);
    cout << endl;
    vec.erase(vec.begin() ,vec.begin()+2);
    prin(vec);
    cout << endl;
    for( vector<string>::iterator it = vec.begin() ;it != vec.end() ;it++ )
    {
    if(*it == "h4")
        it =  vec.erase(it);//前面加不加it都一样，但是在list中不行
    cout << *it << endl;
    }
    cout << "--front--back-size-capacity-max_size-" << endl;// 获得第一个 最后一个元素
    cout << "front :" << vec.front() << " " << "back :" << vec.back() << endl;
  //  vec.insert(vec.end() ,23 ,"hh");
    cout << "size :" <<(int) vec.size()
         << " " << "capacity :" 
         << (int)vec.capacity() << endl; 
    cout << "max_size :" << (int)vec.max_size() << endl;

}
