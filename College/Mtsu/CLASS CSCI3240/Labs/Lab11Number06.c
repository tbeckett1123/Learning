/* Name: 	Timothy Beckett
 * Lab:		11
 * Number:	6
 * Description: Implement a parallel radix sort algorithm in C using pthreads.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define MAX_DIGITS 10

struct ParallelRadixSortParams
{
    int S;
    int D;
};

// Structure way of tracking dynamic memory to free before ending program
struct Garbage
{
    void *Unit;
    struct Garbage *Next;
} *Head = NULL;
void AddToFinalizeList(void *unit);
void Finalize();

int array[10] = { 10, 1, 2, 4, 9, 8, 3, 5, 6, 7 };

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

void ParallelRadixSort(int size);
int GetDigit(int number, int position);
void* CountingSort(void* args);
void PrintArray(int array[], int size);

int main(int argc, char **argv)
{
    sem_init(&empty, 0, 1); // setting up thread magement
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    PrintArray(array, 10);

    ParallelRadixSort(10);

    PrintArray(array, 10);

    sem_destroy(&empty); // cleaning up thread management
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    Finalize();
    return 0;
}

// Add Garbarge to clean
void AddToFinalizeList(void *unit)
{
    if (Head == NULL) // 1 time setup of garbage collection
    {
        Head = (struct Garbage*)malloc(sizeof(struct Garbage));
        Head->Unit = NULL;
        Head->Next = NULL;
    }

    struct Garbage *New = (struct Garbage*)malloc(sizeof(struct Garbage));
    New->Unit = unit;
    New->Next = NULL;
    Head->Next = New;
}

// Free up dynamically created memory
void Finalize()
{
    struct Garbage *current = Head; // setup for freeing loop. node
    while(current != NULL)          // free up each item in the list 
    {
        struct Garbage *temp = current; // prep item to be freeed
        current = current->Next;        // advance the current pointer
        free(temp->Unit);               // free up the item
        free(temp);                     // free up the container
    }
}

void PrintArray(int array[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// Function to get the digit value at a specific position
int GetDigit(int number, int position) 
{
    for (int i = 0; i < position; i++)
        number /= 10;

    return number % 10;
}

// Function to perform counting sort based on a specific digit
void* CountingSort(void *args)
{
     struct ParallelRadixSortParams *params = (struct ParallelRadixSortParams*)args;

    int* count = (int*)calloc(10, sizeof(int));
    int* temp = (int*)malloc(params->S * sizeof(int));

    AddToFinalizeList(count);
    AddToFinalizeList(temp);

     // lock resources
    sem_post(&full); // increment full slots (V function)
    pthread_mutex_lock(&mutex); // wait for thread resources
    sem_wait(&empty); // decrement empty slots (P function)

    // Count the occurrences of each digit
    for (int i = 0; i < params->S; i++) 
    {
        int d = GetDigit(array[i], params->D);
        count[d]++;
    }

    // Calculate the prefix sum
    int sum = 0;
    for (int i = 0; i < 10; i++) 
    {
        int temp = count[i];
        count[i] = sum;
        sum += temp;
    }

    // Perform the sorting
    for (int i = 0; i < params->S; i++) 
    {
        int d = GetDigit(array[i], params->D);
        temp[count[d]] = array[i];
        count[d]++;
    }

    // Copy the sorted elements back to the original array
    for (int i = 0; i < params->S; i++)
        array[i] = temp[i];

    // release resources
    pthread_mutex_unlock(&mutex); // release thread resources
    sem_post(&empty); // increment empty slots (V function)

    return NULL;
}

// Parallel radix sort function
void ParallelRadixSort(int size)
{
    pthread_t threads[MAX_DIGITS];
    int digit;

    for (digit = 0; digit < MAX_DIGITS; digit++) 
    {
        struct ParallelRadixSortParams *params = (struct ParallelRadixSortParams*)malloc(sizeof(struct ParallelRadixSortParams));
        AddToFinalizeList(params);
        params->S = size;
        params->D = digit;

        pthread_create(&threads[digit], NULL, CountingSort, (void*)params);
    }

    for (digit = 0; digit < MAX_DIGITS; digit++)
        pthread_join(threads[digit], NULL);
}



