#include <stdio.h>

int main()
{
   	char ch;
   	char str1[100], str [80];
	int i;

   	printf("Enter any character \n");
   	scanf("%c", &ch);
  	printf("Entered character is %c \n", ch);
   	printf("Enter any string ( upto 100 character ) \n");
   	scanf("%s", &str1);
   	printf("Entered string is %s \n", str);

   // complicated examples
  	printf ("Enter your family name: ");
  	scanf ("%79s",str);  
  	printf ("Enter your age: ");
  	scanf ("%d",&i);
  	printf ("Mr. %s , %d years old.\n",str,i);
  	printf ("Enter a hexadecimal number: ");
  	scanf ("%x",&i);
  	printf ("You have entered %#x (%d).\n",i,i);
  	return 0;
}