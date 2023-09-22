/* Name: 	Timothy Beckett
 * Lab:		11
 * Number:	3
 * Description: Implement a parallel bubble sort algorithm in C using pthreads.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

int array[10] = { 10, 1, 2, 4, 9, 8, 3, 5, 6, 7 };

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

void* SortThread(void* args);
void* PrintThread(void *args);
void BubbleSort(int array[], int size);
void PrintArray(int array[], int size);

int main(int argc, char **argv)
{
    pthread_t sort_thread, print_thread;

    sem_init(&empty, 0, 1); // setting up thread magement
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // lock resources
    sem_post(&full); // increment full slots (V function)
    pthread_mutex_lock(&mutex); // wait for thread resources
    sem_wait(&empty); // decrement empty slots (P function)

    pthread_create(&sort_thread, NULL, SortThread, NULL);
    pthread_create(&print_thread, NULL, PrintThread, NULL);

    pthread_join(sort_thread, NULL); // wait for threads to finish
    pthread_join(print_thread, NULL);

    sem_destroy(&empty); // cleaning up thread management
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}

void* SortThread(void* args)
{
    BubbleSort(array, 10);

    // resources for MultiplyMatrices
    pthread_mutex_unlock(&mutex); // release thread resources
    sem_post(&empty); // increment empty slots (V function)
}

void* PrintThread(void *args)
{
    sem_post(&full); // increment full slots (V function)
    pthread_mutex_lock(&mutex); // wait for thread resources
    sem_wait(&empty); // decrement empty slots (P function)

    PrintArray(array, 10);
}

void BubbleSort(int array[], int size)
{
    int i, j, temp;

    for (i = 0; i < size - 1; i++) 
    {
        for (j = 0; j < size - i - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                // Swap array[j] and array[j+1]
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
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





