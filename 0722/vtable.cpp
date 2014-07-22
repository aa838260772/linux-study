#include <iostream>
#include <string>

using namespace std;

class base
{
    public:
        base(int a = 1)
            :a_(a)
        {
            cout << "base constructor" << endl;
        }

        virtual    ~base()
        {
            cout << "base destructor" << endl;
        }
    private:
        int a_;
};

class derive : public base
{
    public:
        derive()
        {
            cout << "derive constructor" << endl;
        }
        ~derive()
        {
            cout << "derive destructor" << endl;
        }
    private:
        int b_;

};

int main(int argc, const char *argv[])
{
    //     base *b = new derive;
    //   delete b;
    derive d;
}
