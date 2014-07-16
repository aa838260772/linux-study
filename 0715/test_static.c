#include <stdio.h>

int main(int argc, const char *argv[])
{
    static int a = 3;
    a ++;
    printf("%d\n",a) ;
    a = 90;
    printf("%d\n",a) ;
    return 0;
}

