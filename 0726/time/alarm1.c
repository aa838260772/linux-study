#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
void handle(int signum)
{
 printf("1s\n");
 alarm(1);
}

int main(int argc, const char *argv[])
{
     if((signal(SIGALRM, handle)) == SIG_ERR)
         ERR_EXIT("alarm");

     alarm(3);
     
     for(;;)
         pause();

    return 0;
}
