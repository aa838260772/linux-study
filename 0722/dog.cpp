#include <iostream>

using namespace std;

class dog
{
    public:
        dog(const int a = 0, const int b = 0, const int c = 0 )
            :a_(a), b_(b), c_(c)
        {
            cout << a_ <<  b_ << c_ << endl;
        }
    private:
        int a_;
        int b_;
        int c_;
};

int main(int argc, const char *argv[])
{
    dog d1;
    dog d2(1);
    dog d3(1,3);
    dog d4(1,4,7);
    return 0;
}
