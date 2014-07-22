#include <iostream>
#include <string>

using namespace std;

class pthread
{

    public:
        void start()
        {
            pthread_create(&tid_ ,NULL ,threadFunc ,this) ;
        }

       static  void *threadFunc(void *arg);//这个必须在类定义外面实现
        void run()
        {
            sleep(1);
        }

        void join()
        {
            pthread_join(tid_);
        }
    private:
        pthread_t tid_;

}

class produce : public pthread
{
    public:
        void run()
        {
            while(1)
            {
                int data = read()%100;
                cout << "produce a data :" << data << endl;
                buffer_.produce(data);
                sleep(5);
            }
        }
}

class consumer : public pthread
{
    public:
        void run()
        {
            while(1)
            {
                int data = buffer.consumer();
                cout << "consume a data:" << data << endl;
                sleep(1);
            }
        }
}





