// fixing the error to make a correct print-out.
#include <stdio.h>

int main(void)
{ 
    unsigned int a = 1000;
    signed int b = -1;

    if (a > b) 
    	printf("%d is more than ", a);
    	printf("%d\n", b);
    else 
    	printf("%d is less or equal than ", a);
    	printf("%d\n", b);
    return 0;
}  