/* Name: 	Timothy Beckett
 * Lab:		11
 * Number:	1
 * Description: Write a program that uses the fork system call to create a child process that
 * reads a list of integers from the console and finds the sum of the even
 * numbers. The child process should then print the result to the console, and
 * the parent process should wait for the child process to finish before
 * terminating.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <ctype.h>
#include <string.h>

#define SIZE 10

int buffer[SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
int total = 0;
pthread_t threads[SIZE];

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

void* Sum(void* args);

int main(int argc, char **argv)
{
    int i, *iptr;

    printf("parent process spinning up...\n"); // just displaying the process

    pthread_t producer_thread, consumer_thread;

    sem_init(&empty, 0, 1); // setting up thread management
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    for (i = 0; i < SIZE; i++)
    {
        iptr = malloc(sizeof(int));
        *iptr = i;
        // start the thread and pass the element index for the thread to use
        pthread_create(&threads[i], NULL, Sum, (void*)iptr);
    }

    for (i = 0; i < SIZE; i++)
    {
        pthread_join(threads[i], NULL); // wait for thread to finish
    }

    printf("The sum is %d\n", total);

    sem_destroy(&empty); // cleaning up thread management
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}

void* Sum(void* args)
{
    int *i = (int*)args;

    sem_post(&full); // increment full slots (V function)
    pthread_mutex_lock(&mutex); // wait for thread resources
    sem_wait(&empty); // decrement empty slots (P function)

    total += buffer[*i];

    pthread_mutex_unlock(&mutex); // release thread resources
    sem_post(&empty); // increment empty slots (V function)

    free(i);

    pthread_exit(NULL);
}
