#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int main(int argc, const char *argv[])
{
    char *p;
    p = getenv("HOME");
    if(p != NULL)
        printf("%s\n", p);

    return 0;
}
