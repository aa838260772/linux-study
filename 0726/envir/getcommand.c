#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int main(int argc,  char * const argv[])
{
    int opt;
    /*      while(( opt = getopt(argc, argv, "nt:")) != -1)
            {
            printf("opt = %c, optarg = %s, optind = %d, argv[%d] = %s\n",
            opt, optarg, optind, optind, argv[optind]);
            }
            */
    while(1)
    {
        opt = getopt(argc, argv, "nt:");
        if(opt == '?')
        {
            exit(EXIT_FAILURE);
        }
        if(opt == -1){
            break;
        }
        switch(opt)
        {
            case 'n':
                printf("-n\n");
                break;
            case 't': 
                printf("-t %d\n", atoi(optarg));
                break;
        }
    }
    return 0;
}
