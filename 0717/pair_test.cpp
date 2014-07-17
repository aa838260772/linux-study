#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <list>

using namespace std;

int main(int argc, const char *argv[])
{
     pair<int ,string> p1;
     pair<int ,int> p2(4 ,5);
     pair<string ,string> p3(string("hello") ,string("world"));
     p1.first = 1;
     p1.second = "lily";
     
     cout << p2.first << " " << p2.second << endl;
     cout << p3.first << " " << p3.second << endl;

     p2 =  make_pair(1 ,2);
     cout << p2.first << " " << p2.second << endl;
   
     make_pair(string("llo") ,1);
     vector<string> v1;
     vector<list<string> > v2;
     make_pair(v1 ,v2);

}
