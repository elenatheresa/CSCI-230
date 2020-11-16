#include <stdio.h>

#define BLURT printf ("This is line %d of file %s (function %s)\n",\
                      __LINE__, __FILE__, __func__)

void dummy_subroutine()
{
    BLURT;
}

int main ()
{
	printf("Version is %s.\n", __VERSION__);
	printf("Today is %s, Time is %s.\n", __DATE__, __TIME__);
	printf("Base file is %s, Include level is %d.\n", __BASE_FILE__, __INCLUDE_LEVEL__);
    printf("This is line %d.\n", __LINE__);
    printf("This is line %d of file \"%s\".\n", __LINE__, __FILE__);
    BLURT;
    dummy_subroutine();
    return 0;
}