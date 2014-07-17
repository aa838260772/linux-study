//测试list的迭代器失效
#include <iostream>
#include <string>
#include <list>

using namespace std;

int main(int argc, const char *argv[])
{
   list<string> lst;
   lst.push_back("h1");
   lst.push_back("h2");
   lst.push_back("h3");
   lst.push_back("h4");
   lst.push_back("h5");
   lst.push_back("h6");

   for(list<string>::iterator it = lst.begin(); it != lst.end(); ++it){
       cout << *it << endl;    
    }
cout << "---------------------------------"  << endl;
   for(list<string>::iterator it = lst.begin(); it != lst.end(); ++it){
       if(*it == "h3")    
        it =  lst.erase(it);//此次不返回it迭代器会造成迭代器失效，进而出现断错误
    }
   for(list<string>::iterator it = lst.begin(); it != lst.end(); ++it){
       cout << *it << endl;    
    }


}
