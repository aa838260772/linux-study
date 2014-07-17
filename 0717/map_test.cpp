//map的插入，根据key值输出value，下标操作实现元素插入，insert操作实现插入的区别
#include <iostream>
#include <string>
#include <map>
#include <utility>

using namespace std;

int main(int argc, const char *argv[])
{
    map<string ,int> weight;

    weight["lion"] = 200;
    weight["cat"] = 10;
    weight["dog"] = 40;

    cout << weight["cat"] << endl;

    weight["cat"] = 20;//实现了对value的更新        
    weight["bird"] = 1;//实现了bird的插入

    map<string ,int>::iterator iter = weight.begin();

    while(iter != weight.end())//输出map的元素
    {
    cout << iter -> first  << " " << iter -> second << endl;
    iter++;
    }

    weight.insert( weight.begin(),make_pair("dog" , 88));//此次插入失败，
    weight.insert( make_pair("elephent" , 888));//此次插入成功
   
    cout << "------------------------------------------------" << endl;
    
     iter = weight.begin();
    while(iter != weight.end())
    {
    cout << iter -> first  << " " << iter -> second << endl;
    iter++;
    }
    return 0;
}
