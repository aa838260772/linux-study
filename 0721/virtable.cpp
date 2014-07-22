#include <iostream>
#include <string>
typedef void(*fun)(void);
using namespace std;

class parent
{
    public:
        int iparent ;
        parent():iparent(10){}
        virtual void f() 
        {
            cout << "parent::f()" << endl;
        }

        virtual void g()
        {
            cout << "parent::g()" << endl;
        }

        virtual void h()
        {
            cout << "parent::h()" << endl;
        }
};

class child : public parent
{
    public:
        int ichild;
        child():ichild(100)
    {}
        virtual void f()
        {
            cout << "child::f()" << endl;
        }

        virtual void g()
        {
            cout << "child::g()" << endl;
        }

        virtual void h()
        {
            cout << "child ::h()" << endl;
        }
};

class grand_child : public child
{
    public:
        int grand_ichild;
        grand_child():grand_ichild(1000)
    {}
        virtual void f()
        {
            cout << "grand_child::f()" << endl;
        }

        virtual void g()
        {
            cout << "grand_child::g()" << endl;
        }
    
         void h()
        {
            cout << "grand_child ::h()" << endl;
        }
       virtual void l()
        {
        cout << "grand_child::l()" << endl;
        }
};

int main(int argc, const char *argv[])
{
    grand_child gc;
    int **pvtab = (int **)&gc;

    cout << "[0] grand_child::vptr->" << endl;

    fun pfun;
    for(int i = 0 ; (fun)pvtab[0][i] != NULL ;i++)
    {
    pfun = (fun)pvtab[0][i];
    cout << "     ["<< i << "]";
    pfun();
    }
  /*  cout << "----------------------------------------" << endl;
    for(int i = 0 ; (fun)pvtab[1][i] != NULL ;i++)
    {
    pfun = (fun)pvtab[0][i];
    cout << "     ["<< i << "]";
    pfun();
    }
*/
    cout << "[1] parent.iparent = "<< (int)pvtab[1] << endl;
    cout << "[2] child.iparent = "<< (int)pvtab[2] << endl;
    cout << "[3] grand_child.iparent = "<< (int)pvtab[3] << endl;

    return 0;
}












