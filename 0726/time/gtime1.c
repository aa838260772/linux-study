#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int main(int argc, const char *argv[])
{
    time_t tt;
    tt = time(NULL);//time(&tt);
    struct tm *pt = gmtime(&tt);
    printf("%d\n", tt);
    printf("%04d-%02d-%02d-%02d-%02d-%02d\n",
            1900 + pt->tm_year,
            1 + pt->tm_mon,
            pt->tm_mday,
            8 + pt->tm_hour,
            pt->tm_min,
            pt->tm_sec
            );
    return 0;
}

