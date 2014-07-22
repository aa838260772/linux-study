#include "handle.h"
#include "animal.h"
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, const char *argv[])
{
    vector<handle> vec;
    dog d1, d2;
    cat c;
    bear b1, b2, b3;

    vec.push_back(d1);
    vec.push_back(d2);
    vec.push_back(c);
    vec.push_back(b1);
    vec.push_back(b2);
    vec.push_back(b3);

    for(vector<handle>::iterator it = vec.begin(); it != vec.end(); ++it){
        (*it)->display();
    }
    
    return 0;
}
