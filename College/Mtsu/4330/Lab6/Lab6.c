/* Programmer:		Timothy Beckett
 * Instructor:		Dr. Pettey
 * Date Due:		04-25-2007
 * Purpose:		This program will read in up to 
 * 			50 integers from the file Lab6.dat
 * 			Then it will preform a quicksort
 * 			in parellel using the desired
 * 			number of threads, specified by the
 * 			user, up to 10 threads. 
 * Techical Specs:	The implementation of parallelism is
 * 			done with pthreads.
 * Inputs:		The number of processors to be used
 * 			will come from the console at exicution
 * 			of the program or from standard in after
 * 			the program has launched.
 * 			The integers will come from a file stream;
 * 			the expected file name is Lab6.dat
 * Outputs:		The sorted integers will be written to a
 * 			file; the file name is Lab6Sorted.dat
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# define MAX_NUMBER 50
# define MAX_THREAD 10
# define TRUE 1
# define FALSE 0

/* global memory */
int count, iArray[MAX_NUMBER];

/* used to assign subsections of the array to threads*/
int uBound[MAX_THREAD], lBound[MAX_THREAD];

/* line  35    prototypes */
/* line  85 */ void ParallelPartition(int threadCount);
/* line 107 */ int  ReadNumbers(char* fn);
/* line 144 */ void WriteNumbers(char* fn);
/* line 179 */ void Spawn(pthread_t id[], int idIndex[], int threadCount);
/* line 195 */ void Finalize(pthread_t id[], int threadCount);
/* line 204 */ void Swap(int* one, int* two);
/* line 217 */ void SerialPartition(int theArr[], int first, int last, int* pivotIndex);
/* line 251 */ void SerialQuickSort(int theArr[], int first, int last);
/* line 265 */ void* Thread(void* id);

int main(int argc, char** argv) /* line 46 */
{
	int threadCount, idIndex[MAX_THREAD], i;
	
	pthread_t id[MAX_THREAD];

	if(argc != 2)
	{
		printf("Enter the number of threads to spawn (2-10):\n");
		scanf("%d", &threadCount);
	}
	else
		threadCount = atoi(argv[1]); /* get from console the 
					      * number of threads to
					      * spawn
					      * * * * * * * * * * */

	i = ReadNumbers("Lab6.dat");

	if( threadCount > 1 && threadCount <= MAX_THREAD && i )
	{
		ParallelPartition(threadCount);
		
		Spawn(id, idIndex, threadCount);

		Finalize(id, threadCount);

		WriteNumbers("Lab6Sorted.dat");

	}
	else
		printf("<******ERROR*******>\nFile opened status %d\nThread Range (2-10) %d\n", i, threadCount);
	
	return 0;
	
}/* end main */

/* This function sets up the partitioning information for the threads.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void ParallelPartition(int threadCount)
{
	int i, pivot;

	lBound[0] = 0;
	
	for(i = 0; i < threadCount - 1; i++) 
	{
		SerialPartition(iArray, lBound[i], count - 1,  &pivot);

		uBound[i] = pivot;
		lBound[i+1] = pivot + 1;
	}

	uBound[i] = count - 1;

}/* End parallel partition */

/* This function reads MAX_NUMBER of integers from the specified file,
 * and puts them in the iArray along with the number of integers read
 * in is put into count
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int ReadNumbers(char* fn)
{
	FILE* fp;
	int r = TRUE, s = TRUE;

	/* if file fails to open return false other wise return true */
	if(fp = fopen(fn, "r")) 
	{
		count = 0; /* set inital count to zero */
		
		/* if file ends or the maxium number of integers have
		 * been read in stop looping 
		 * * * * * * * * * * * * * * * * * * * * * * * * * * */
		while(!feof(fp) && s)
			if(count < MAX_NUMBER + 1)
				fscanf(fp, "%d", &iArray[count++]);
			else
				s = FALSE;
		
		fclose(fp);

		count--;
		
		if(count == MAX_NUMBER) printf("The maxium number set %d has been reached\n", MAX_NUMBER);
		
		system("cat Lab6.dat");

		puts("\n");
	}
	else
		r = FALSE;
	
	return r;
	
}/* end read numbers */

/* This function will write to the specified file the numbers
 * stored in iArray. 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void WriteNumbers(char* fn)
{
	FILE* fp;
	int i;
	char *otpt,  *output;

	otpt = (char*)malloc((strlen(fn) + 6) * sizeof(char));

	otpt[0] = 'c';
	otpt[1] = 'a';
	otpt[2] = 't';
	otpt[3] = ' ';
	otpt[4] = '\0';

	output = strcat(otpt, fn);
	
	fp = fopen(fn, "w");
	
	for(i = 0; i < count; i++)
		fprintf(fp, "%d ", iArray[i]);

	fclose(fp);

	printf("The sorted list of numbers is in the file %s\n", fn);
	
	/* output: cat <filename> */
	system(output);

	puts("\n");

	free(otpt);
	
}/* end write numbers */

/* This function will create the desired number of threads */
void Spawn(pthread_t id[], int idIndex[], int threadCount)
{
	int i;

	for(i = 0; i < threadCount; i++)
	{
		idIndex[i] = i;

		pthread_create(&id[i], NULL, Thread, (void *)&idIndex[i]);
	}
	
}/* end spawn */

/* This function is designed to work in conjunction with Spawn.
 * It will shutdown and clean up the desired number of threads
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Finalize(pthread_t id[], int threadCount)
{
	int i;

	for(i = 0; i < threadCount; i++)
		pthread_join(id[i], NULL);
	
}/* end finalize */

void Swap(int* one, int* two)
{
	int temp;

	temp = *one;
	*one = *two;
	*two = temp;
	
}/* end swap */

/* This function does the sorting for one interatation of the Serial 
 * Quicksort function 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void SerialPartition(int theArr[], int first, int last, int* pivotIndex)
{

	int pivot,
	    lastS1,
	    firstUnknown,
	    temp;

	pivot = theArr[first];
	
	lastS1 = first;
	
	firstUnknown = first + 1;

	for(; firstUnknown <= last; ++firstUnknown)
	{
		if(theArr[firstUnknown] < pivot)
		{
			++lastS1;

			Swap(&theArr[firstUnknown], &theArr[lastS1]);
		}
	}

	Swap(&theArr[first], &theArr[lastS1]);

	*pivotIndex = lastS1;
		
}/* end Serial partition */

/* This is function preforms a quicksort on the desired array.
 * With proper indexing the sort can be preformed on a sub-
 * section of an array.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void SerialQuickSort(int theArr[], int first, int last)
{
	int pivotIndex;

	if(first < last)
	{
		SerialPartition(theArr, first, last, &pivotIndex);

		SerialQuickSort(theArr, first, pivotIndex - 1);
		SerialQuickSort(theArr, pivotIndex + 1, last);
	}
}/* end Serial quicksort */


/* The function is designed to call a serial quicksort on a
 * global array of integers.  Each thread will preform the 
 * sort on its subsection of the array based on the upper
 * and lower bounds provided in lBound and uBound.
 * */
void * Thread(void * id)
{
	int first, last;
	int iid = *((int*)id);

	first = lBound[iid];
	last = uBound[iid];

	SerialQuickSort(iArray, first, last);
	
	pthread_exit(0);
	
}/* end thread */

