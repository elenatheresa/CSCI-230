#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// constants
#define BUFFSIZE 16
#define MAX_CHARS 64
#define NUM_CHILDS 5

// mutexes
pthread_mutex_t mutex;

/* parent threads */
void* parent_producer(void* id);
void* parent_consumer(void* id);

/* child threads */
void* child_producer(void* id);
void* child_consumer(void* id);


/* shared memory buffer */
int buffer[BUFFSIZE] = { 0 };
int buffer_count = 0;  // number of items in buffer
int in = 0;  // bufer pointers
int out = 0;
// track consumers turns
int cons_seq_num[NUM_CHILDS + 1] = { 0 };
int cons_seq_count = 0;
// track producer turns
int prod_seq_num[NUM_CHILDS + 1] = { 0 };
int prod_seq_count = 0;

/* program starts here */
int	main(int argc, char* argv[])
{

	// print program title
	printf("Program 1 Producer-Consumer Shuffle contents of 5 files\n");

	// initilize mutex
	pthread_mutex_init(&mutex, NULL);

	/* parent threads */
	pthread_t prod_t;
	pthread_t cons_t;

	/* parent thread id's */
	int prodid = 1;
	int consid = 2;

	/* create parent producer thread */
	pthread_create(&prod_t, NULL, parent_producer, (void*)& prodid);

	/* create parent consumer threads */
	pthread_create(&cons_t, NULL, parent_consumer, (void*)& consid);


	/* wait fot threads to complete */
	pthread_join(prod_t, NULL);
	pthread_join(cons_t, NULL);


	/* destroy mutex*/
	pthread_mutex_destroy(&mutex);

	return	0;
}


/* parent producer thread */
void* parent_producer(void* id)
{
	int i = 0;
	printf("parent producer thread starting\n");

	// thread stuff
	pthread_t child_t[NUM_CHILDS];
	int child_id[NUM_CHILDS];

	// make 5 child producer threads
	for (i = 0; i < NUM_CHILDS; i++)
	{
		child_id[i] = (i + 1);
		pthread_create(&child_t[i], NULL, child_producer, (void*)& child_id[i]);
	}

	// wait for child threads to complete
	for (i = 0; i < NUM_CHILDS; i++)
	{
		pthread_join(child_t[i], NULL);
	}


	pthread_exit(NULL);

}



/* parent consumer thread */
void* parent_consumer(void* id)
{
	int i = 0;

	printf("parent consumer thread starting\n");

	// thread stuff
	pthread_t child_t[NUM_CHILDS];
	int child_id[NUM_CHILDS];

	// make 5 child producer threads
	for (i = 0; i < NUM_CHILDS; i++)
	{
		child_id[i] = (i + 1);
		pthread_create(&child_t[i], NULL, child_consumer, (void*)& child_id[i]);
	}

	// wait for child threads to complete
	for (i = 0; i < NUM_CHILDS; i++)
	{
		pthread_join(child_t[i], NULL);
	}


	pthread_exit(NULL);


}


/* child producer thread */

// read file, write to buffer
void* child_producer(void* id) {

	int i = 0;

	// get child id
	int child_id = *(int*)(id);

	printf("child producer thread %d starting\n", child_id);

	// add numner to input file name
	char filename[MAX_CHARS];

	// add file number
	sprintf(filename, "%s%d%s", "input", child_id, ".txt");

	printf("child producer %d input file name %s\n", child_id, filename);

	// open file for read 
	FILE* fp = fopen(filename, "r");
	if (fp == 0) {
		printf("child producer %d cannot open input file: %s\n", child_id, filename);
		exit(0);
	}

	printf("child producer %d starting\n",child_id);

	int number = 0;
	char comma = ',';

	// loop till exit 
	do
	{
	
		// critical section enterred
		pthread_mutex_lock(&mutex);

		// can write if buffer not filled
		if (buffer_count < BUFFSIZE)
		{

			// if the child producer has not read yet
			if (prod_seq_num[child_id] == 0)
			{
				prod_seq_num[child_id] = 1;  // signal has read

				// check if read sequence over
				prod_seq_count++;
				if (prod_seq_count == NUM_CHILDS)
				{
					// clear for next sequence
					for (i = 0; i <= NUM_CHILDS; i++)
					{
						prod_seq_num[i] = 0;
					}

					prod_seq_count = 0;
				}

				// test if end of file
				if (feof(fp) || comma != ',')
				{
					number = -1;
				}

				else
				{
					// read int from file
					fscanf(fp, "%d%c", &number, &comma);
					//printf("child producer %d writes number %d to file\n", child_id, number);
				}

				// write number to buffer
				buffer[in] = number;
				buffer_count++;

				// update the in 
				in = (in + 1) % BUFFSIZE;
			}

		}

		// leave critical area
		pthread_mutex_unlock(&mutex);

	} while (number != -1); // loop till no more numbers read from file

	// producer done
	printf("child producer %d done\n", child_id);

	fclose(fp); // close input file

	pthread_exit(NULL);
}



/* child consumer  thread */

// read char from buffer and write to file
void* child_consumer(void* id) {

	int i = 0;

	// get child id
	int child_id = *(int*)(id);

	printf("child consumer thread %d starting\n", child_id);

	// add numner to input file name
	char filename[MAX_CHARS] = "";

	// add file number
	sprintf(filename, "%s%d%s", "output", child_id, ".txt");

	printf("child consumer %d output file name %s\n", child_id, filename);

	// open file for write
	FILE* fp = fopen(filename, "w");
	if (fp == 0) {
		printf("child consumer %d cannot open output file: %s\n", child_id, filename);
		exit(0);
	}

	printf("child consumer %d starting\n",child_id);

	int number = 0;

	// loop till exit 
	do
	{
	
		// critical section enterred	
		pthread_mutex_lock(&mutex);

		// print out buffer
		//for (int i = 0; i < BUFFSIZE; i++)
		//{
		//	printf("%d ", buffer[i]);
		//}

		//printf("\n");


	// cannot read buffer if count 0
		if (buffer_count > 0)
		{

			// read number from buffer
			number = buffer[out];

			// generate random number for shuffling
			int x = (rand() % NUM_CHILDS) + 1;

			// if child not read yet and random number match 
			if ((cons_seq_num[child_id] == 0) || (number == -1))
			{
				if (((number / 10000) == x) || (number == -1))
				{

					// signal child read number from buffer
					cons_seq_num[child_id] = 1;
					buffer_count--;

					// write number to file
					if (number != -1)
					{
						fprintf(fp, "%d%c ", number, ',');
						//printf("child consumer %d reads number %d from buffer\n", child_id, number);
					}

					// update the out 
					out = (out + 1) % BUFFSIZE;

					// update sequence  seq count
					cons_seq_count++;

					// end of sequence?
					if (cons_seq_count >= NUM_CHILDS)
					{

						// cleat for next sequence
						for (i = 0; i <= NUM_CHILDS; i++)
						{
							cons_seq_num[i] = 0;
						}

						cons_seq_count = 0;

					}
				}
			}

		}

		// leave critical area
		pthread_mutex_unlock(&mutex);


	} while (number != -1);

	// consumer done
	printf("child consumer %d done\n", child_id);

	fclose(fp); // close input file

	pthread_exit(NULL);
}

///////////////////////////////////////////////////////////////////////////////////////

