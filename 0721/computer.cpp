#include <iostream>
#include <string>

using namespace std;

class computer
{
    public:
        virtual void prin()
    {
    cout << "computer" << endl;
    }
    virtual void price()
    {
        cout << "computer price" << endl;
    }
};

class dell : public computer
{
    public:
        dell(int price = 700)
            :price_(price)
        {}
        void  price()
        {
            cout << "dell :$" << price_ <<endl;
        }
    private:
        int price_;
};

class lenovo : public computer
{
    public:
        lenovo(int price = 800)
            :price_(price)
        {}
        void   price()
        {
            cout << "lenovo :$" << price_ << endl;
        }
    private:
        int price_;
};

class mac : public computer
{
    public:
        mac(int price = 1200)
            :price_(price)
        {}

        void  price()
        {
            cout << "mac : $" << price_ << endl;
        }
    private:
        int price_;
};

int main(int argc, const char *argv[])
{
    dell d(900);
    lenovo le;
    mac ma;

    computer *c1 = &d;
    computer *c2 = &le;
    computer *c3 = &ma;
    computer *c4 = new computer;

    c1->price();
    c2->price();
    c3->price();
    c4->price();

    delete c4;
}




