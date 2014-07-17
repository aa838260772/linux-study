#include <iostream>
#include <set>

using namespace std;

int main(int argc, const char *argv[])
{
    set<int> e;
   e.insert(56);
   e.insert(34);
   e.insert(3);
   e.insert(12);

   for(set<int>::iterator iter = e.begin() ; iter != e.end() ;iter++)
   {
   cout << *iter << endl;
   }

   cout << "-------------------------------" << endl;
   e.erase(12);
   for(set<int>::iterator iter = e.begin() ; iter != e.end() ;iter++)
   {
   cout << *iter << endl;
   }

    return 0;
}
