#include <stdio.h>
#include <string.h>

const int arraySize_Dim1 = 4;
const int arraySize_Dim2 = 5;
char output_str[300];
char tmp_str[5];

int test_2D[][arraySize_Dim2] = {
			{-1, -2, -3, -4, -5} ,
			{-6, -7, -8, -9, -10} ,
			{-11, -12, -13, -14, -15} ,
			{-16, -17, -18, -19, -20}
	};

int data_2D[arraySize_Dim1][arraySize_Dim2];
int data_1D[arraySize_Dim1*arraySize_Dim2];

void printarray(int array[][arraySize_Dim2], int Dim1, int Dim2)
{
    int i;
    int j;

    for( j = 0; j < Dim1; j++ ) {
        for( i = 0; i < Dim2; i ++) {
            printf( "%4d ", array[j][i] );
        }
        printf("\n");
	}
	printf("-----------------------\n");
}

int main(void)
{
	// Initializing the 2D array
	int k = 0;
	int remainder;
	int quotient;

	printarray(test_2D, arraySize_Dim1, arraySize_Dim2);

	for (int i = 0; i < arraySize_Dim1; i++) {
    	for (int j = 0; j < arraySize_Dim2; j++) {
        	data_2D[i][j] = k++;
    	}
	}

	// Printing the 2D array
	strcpy(output_str, "    ");
	for (int j = 0; j < arraySize_Dim2; j++) {
		sprintf(tmp_str, "%2d  ", j);
		strcat(output_str, tmp_str);
	}
	printf("%s\n", output_str);
	printf("--+--------------------\n");

	for (int i = 0; i < arraySize_Dim1; i++) {
		sprintf(output_str, "%d | ", i);
		for (int j = 0; j < arraySize_Dim2; j++) {
        	sprintf(tmp_str, "%2d  ", data_2D[i][j]);
        	strcat(output_str, tmp_str);
    	}
    	printf("%s\n", output_str);
	}
	printf("\n");

	// converting 2D to 1D
	for (int i = 0; i < arraySize_Dim1*arraySize_Dim2; i++) {
		remainder = i % arraySize_Dim2;
		quotient = (i - remainder)/arraySize_Dim1;
        data_1D[i] = data_2D[quotient][remainder];
 	}

	// Printing the 1D array
	strcpy(output_str, "   ");
	for (int j = 0; j < arraySize_Dim1*arraySize_Dim2; j++) {
		sprintf(tmp_str, "%2d ", j);
		strcat(output_str, tmp_str);
	}
	printf("%s\n", output_str);
	printf("--+------------------------------------------------------------\n");

	strcpy(output_str, "  |");
	for (int i = 0; i < arraySize_Dim1*arraySize_Dim2; i++) {
        sprintf(tmp_str, "%2d ", data_1D[i]);
        strcat(output_str, tmp_str);
    }
    printf("%s\n", output_str);
}