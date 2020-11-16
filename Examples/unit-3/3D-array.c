#include <stdio.h>
#include <string.h>

const int arraySize_Dim1 = 4;
const int arraySize_Dim2 = 5;
char output_str[300];
char tmp_str[5];

int test[2][3][4] = { 
                     { {3, 4, 2, 3}, {0, -3, 9, 11}, {23, 12, 23, 2} },
                     { {13, 4, 56, 3}, {5, 9, 3, 5}, {3, 1, 4, 9} }
                 };
                 
int data_2D[arraySize_Dim1][arraySize_Dim2];
int data_1D[arraySize_Dim1*arraySize_Dim2];

int main(void)
{
	// Initializing the 2D array
	int k = 0;
	int remainder;
	int quotient;

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