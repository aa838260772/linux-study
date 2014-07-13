/*
 *文件按单词输出
 *
 */
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

int main(int argc, const char *argv[])
{
    string s("cin_cout.cpp");
    ifstream infile(s.c_str());
    string s_word;
    while(infile >> s_word)
    {
    cout << s_word <<endl;
    }

    return 0;
}
