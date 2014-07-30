#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

pthread_once_t once_control = PTHREAD_ONCE_INIT;
void test()
{
    printf("test once---------------------\n");//即使是多线程，此函数也只执行一次
}

void * pthreadfunc(void *arg)
{
    pthread_detach(pthread_self());
    pthread_once(&once_control, test);
    printf("pid: %u\n", (unsigned long int)pthread_self());
    pthread_exit(NULL);
}

int main(int argc, const char *argv[])
{
    pthread_t pid[10];
     int i;
     for(i = 0; i < 10; ++i)
     {
     pthread_create(&pid[i], NULL, pthreadfunc, NULL);
     }
    return 0;
}
