#include <stdio.h>

int main ()
{
    #define FOO 4
    int x = FOO;
    printf("x = %d\n", x);
    #undef FOO
    #define FOO 5
    x = FOO;
    printf("x = %d\n", x);

    #define BUFSIZE 1020
    #define TABLESIZE BUFSIZE
    printf("TABLESIZE = %d\n", TABLESIZE);
    #undef BUFSIZE
    #define BUFSIZE 37
    printf("TABLESIZE = %d\n", TABLESIZE);
    return 0;
}