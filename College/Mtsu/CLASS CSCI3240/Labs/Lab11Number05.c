/* Name: 	Timothy Beckett
 * Lab:		11
 * Number:	5
 * Description: Implement a parallel quicksort algorithm in C using pthreads
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

struct QuickSortParams
{
    int L;
    int H;
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

void Swap(int* a, int* b);
int Partition(int array[], int low, int high);
void* QuickSort(void *args);
void PrintArray(int array[], int size);

int main(int argc, char **argv)
{
    pthread_t sort_thread, print_thread;

    sem_init(&empty, 0, 1); // setting up thread magement
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    PrintArray(array, 10);

    struct QuickSortParams *params = (struct QuickSortParams*)malloc(sizeof(struct QuickSortParams));
    params->L = 0;
    params->H = 9;
    AddToFinalizeList(params);

    pthread_create(&sort_thread, NULL, QuickSort, (void*)params);

    pthread_join(sort_thread, NULL); // wait for threads to finish

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

// Swap two elements
void Swap(int* a, int* b) 
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition the array using the last element as the pivot
int Partition(int array[], int low, int high)
{
    int pivot = array[high];  // Choose the last element as the pivot
    int i = low - 1;  // Index of the smaller element

    for (int j = low; j <= high - 1; j++) {
        // If the current element is smaller than or equal to the pivot
        if (array[j] <= pivot) {
            i++;  // Increment index of the smaller element
            Swap(&array[i], &array[j]);
        }
    }
    Swap(&array[i + 1], &array[high]);
    return (i + 1);
}

// Quicksort algorithm
void* QuickSort(void *args)
{
    pthread_t p1, p2;
    struct QuickSortParams *arr0 = (struct QuickSortParams*)args;

    if (arr0->L < arr0->H)
    {
        // lock resources
        sem_post(&full); // increment full slots (V function)
        pthread_mutex_lock(&mutex); // wait for thread resources
        sem_wait(&empty); // decrement empty slots (P function)

        // Partition the array into two parts
        int pi = Partition(array, arr0->L, arr0->H);

        // release resources
        pthread_mutex_unlock(&mutex); // release thread resources
        sem_post(&empty); // increment empty slots (V function)

        struct QuickSortParams *arr1 =  (struct QuickSortParams*)malloc(sizeof(struct QuickSortParams));
        struct QuickSortParams *arr2 =  (struct QuickSortParams*)malloc(sizeof(struct QuickSortParams));
        AddToFinalizeList(arr1);
        AddToFinalizeList(arr2);

        arr1->L = arr0->L;
        arr1->H - pi - 1;
        arr2->L = pi + 1;
        arr2->H = arr0->H;

        // Recursively sort the sub-arrays
        pthread_create(&p1, NULL, QuickSort, (void*)arr1);
        pthread_create(&p2, NULL, QuickSort, (void*)arr2);

        pthread_join(p1, NULL); // wait for threads to finish
        pthread_join(p2, NULL);
    }

    return NULL;
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





