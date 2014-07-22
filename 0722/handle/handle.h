#ifndef _HANDLE_H_
#define _HANDLE_H_

class animal;//前向声明

class handle
{
    public:
        handle();
        handle(const animal &);
        handle(const handle &);
        handle &operator=(const handle &);
        ~handle();

        animal *operator->();
        const animal *operator->() const;

    private:
            animal *ptr_;
};
#endif /*HANDLE_H*/ 
