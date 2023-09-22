/* Name: 	Timothy Beckett
 * Lab:		11
 * Number:	4
 * Description: Implement a parallel merge sort algorithm in C using pthreads.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

struct MergeSortParams
{
    int L;
    int R;
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

void Merge(int l, int m, int r);
void* MergeSort(void *args);
void PrintArray(int array[], int size);

int main(int argc, char **argv)
{
    pthread_t sort_thread;

    PrintArray(array, 10);

    struct MergeSortParams *params = (struct MergeSortParams*)malloc(sizeof(struct MergeSortParams));
    params->L = 0;
    params->R = 9;
    AddToFinalizeList(params);

    pthread_create(&sort_thread, NULL, MergeSort, (void*)params);

    pthread_join(sort_thread, NULL); // wait for threads to finish

    PrintArray(array, 10);

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

// Merge sort function
void* MergeSort(void *args)
{
    pthread_t p1, p2;
    struct MergeSortParams *arr0 = (struct MergeSortParams*)args;

    if (arr0->L < arr0->R)
    {
        struct MergeSortParams *arr1 =  (struct MergeSortParams*)malloc(sizeof(struct MergeSortParams));
        struct MergeSortParams *arr2 =  (struct MergeSortParams*)malloc(sizeof(struct MergeSortParams));
        AddToFinalizeList(arr1);
        AddToFinalizeList(arr2);

        // Same as (l+r)/2, but avoids overflow for large l and r
        int m = arr0->L + (arr0->R - arr0->L) / 2;

        arr1->L = arr0->L;
        arr1->R = m;

        arr2->L = m + 1;
        arr2->R = arr0->R;

        // Sort first and second halves
        pthread_create(&p1, NULL, MergeSort, (void*)arr1);
        pthread_create(&p2, NULL, MergeSort, (void*)arr2);

        pthread_join(p1, NULL); // wait for threads to finish
        pthread_join(p2, NULL);

        // Merge the sorted halves
        Merge(arr0->L, m, arr0->R);
    }

    return NULL;
}

// Merge two subarrays of array[]
// First subarray is array[l..m]
// Second subarray is array[m+1..r]
void Merge(int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temporary arrays
    int L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = array[l + i];
    for (j = 0; j < n2; j++)
        R[j] = array[m + 1 + j];

    // Merge the temporary arrays back into array[l..r]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) 
    {
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        } else {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) 
    {
        array[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) 
    {
        array[k] = R[j];
        j++;
        k++;
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





