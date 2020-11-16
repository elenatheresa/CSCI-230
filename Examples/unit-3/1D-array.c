#include <stdio.h>

const int arraySize = 5;

int test[arraySize] = {0, -1, -4, -9, -16};

float summation(int data[])
{
	float P = 0.0;
   	for (int i = 0; i < arraySize; i++) {
    	P+= (float)data[i];
   	}
   	return P;
}

int main(void)
{
	int data[arraySize];
	printf("Summation of test is %f\n", summation(test));

   	for (int i = 0; i < arraySize; i++) data[i] = i*i;
   	printf("Summation of data is %f\n", summation(data));
}
