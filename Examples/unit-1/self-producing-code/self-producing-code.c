#include <stdlib.h>
#include <stdio.h>

int main()
{
	char q=34,n=10, *a="int main() {char q=34,n=10,*a=%c%s%c; printf(a,q,a,q,n);}%c";
	printf(a,q,a,q,n);
}