#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#define ERR_EXIT(m) \
    do {\
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int main(int argc, const char *argv[])
{
    pid_t pid;
    if((pid = fork()) == -1)
        ERR_EXIT("fork");
    else if(pid == 0)
    {
        exit(EXIT_SUCCESS);
    }else
    {
        int ret = wait(NULL);
        printf("child = %d\n", ret);
        while(1);
    }
    return 0;
}
