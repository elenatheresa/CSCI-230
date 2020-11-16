#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>


int* a = 0;  // array to sort


// keep track of boundariers
typedef struct ArrayIndexType {
	int low;
	int high;
} ArrayIndex;


// merge between high and low at midpoint
void merge(int low, int high)
{
	// counters
	int i = 0;
	int cur = 0;

	// find midpoint
	int mid = (low + high) / 2;

	// set left and right
	int left = low;
	int right = mid + 1;

	// temporary array for sorting
	int b[high - low + 1];

	// put numbers into b sorted
	while (left <= mid && right <= high) {
		if (a[left] > a[right])
			b[cur++] = a[right++];
		else
			b[cur++] = a[left++];
	}

	// rest of left side
	while (left <= mid) b[cur++] = a[left++];

	// rest of right side
	while (right <= high) b[cur++] = a[right++];

	// put sorted part back into a
	for (i = 0; i < (high - low + 1); i++)
	{
		a[low + i] = b[i];
	}
}

// merge sort thread
void* mergesort(void* indexes)
{
	int i = 0;

	// indexes high and low
	ArrayIndex* pindexes = (ArrayIndex*)indexes;

	// input sequence to the thread
	printf("input sequence to the thread\n");
	for (i = pindexes->low; i <= pindexes->high; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");

	// find mid point
	int mid = (pindexes->low + pindexes->high) / 2;

	ArrayIndex aIndex[2];
	pthread_t thread[2];

	// left side
	aIndex[0].low = pindexes->low;
	aIndex[0].high = mid;

	// right side
	aIndex[1].low = mid + 1;
	aIndex[1].high = pindexes->high;

	// input sequence to the thread
	printf("left side sequence after splitting\n");
	for (i = aIndex[0].low; i <= aIndex[0].high; i++)
	{
		printf("%d ", a[i]);
	}

	printf("\n");

	// right sequence to the thread
	printf("right side sequence after splitting\n");
	for (i = aIndex[1].low; i <= aIndex[1].high; i++)
	{
		printf("%d ", a[i]);
	}

	printf("\n");


	// none to merge
	if (pindexes->low >= pindexes->high) return 0;


	// make megere sort child threads

	pthread_create(&thread[0], NULL, mergesort, &aIndex[0]);
	pthread_create(&thread[1], NULL, mergesort, &aIndex[1]);

	// wait for children to finish
	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);


	// merge two sides
	merge(pindexes->low, pindexes->high);

	// single sequence after merging
	printf("single sequence after merging\n");
	for (i = pindexes->low; i <= pindexes->high; i++)
	{
		printf("%d ", a[i]);
	}

	printf("\n");

	pthread_exit(NULL);
}

// command line receives length of random orders of numbers
// run program like this
// program2 100

int main(int argc, char* argv[])
{
	int i = 0;

	// check command line for length of numbers
	if (argc != 2)
	{
		printf("usage: program2 <length of random numbers>\n");
		printf("example: program2 100\n");
		return 0;
	}

	int n = atoi(argv[1]);

	if (n <= 0)
	{
		printf("length must be greater than 0\n");
		return 0;
	}

	// make random array of numbers
	a = (int*)malloc(sizeof(int) * n);

	// fill array with random nuumbers
	srand((unsigned int)time(0));

	for (i = 0; i < n; i++)
	{
		a[i] = rand() % 10;

	}

	printf("un sorted array\n");
	for (i = 0; i < n; i++) printf("%d ", a[i]);
	printf("\n");


	ArrayIndex ai;
	ai.low = 0;
	ai.high = n - 1;
	pthread_t thread;

	// create parent thread
	pthread_create(&thread, NULL, mergesort, &ai);

	// wait till done
	pthread_join(thread, NULL);

	// print out sorted array
	printf("final sorted array\n");
	for (i = 0; i < n; i++) printf("%d ", a[i]);
	printf("\n");

	free(a);

	return 0;
}





