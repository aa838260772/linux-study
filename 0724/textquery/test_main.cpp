#include "textquery.h"

using namespace std;

int main(int argc, const char *argv[])
{
    textquery tq;
    ifstream is("nonblock.c");
    tq.read_file(is);

    string word;
    while( cin >> word)
    {
    tq.prin(word);
    }
    is.close();
    return 0;
}
