/* Name: 	Timothy Beckett
 * Lab:		11
 * Number:	2
 * Description: Write a C program to implement a multi-threaded matrix multiplication using
 * pthreads.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

int *matrix1, m1Rows, m1Columns, *matrix2, m2Rows, m2Columns, *matrix3, m3Rows, m3Columns;

sem_t empty_prod;
sem_t full_prod;
pthread_mutex_t mutex_prod;

sem_t empty_print;
sem_t full_print;
pthread_mutex_t mutex_print;

void GetMatrixSize(char* label, int *columns, int *rows);
int* GetMatrixWithValues(char* label, int columns, int rows);
int* NewArray(int size);
void Print(char *message, int *matrix, int columns, int rows);
int* Product(int *matrix1, int *matrix2, int m1Columns, int m1Rows, int m2Columns, int m2Rows, int *m3Columns, int *m3Rows);

void* GetMatricesThread(void *args);
void* MultiplyMatricesThread(void *args);
void* PrintMatricesThread(void *args);

int main(int argc, char **argv)
{
    matrix1 = NULL;
    matrix2 = NULL;
    matrix3 = NULL;

    pthread_t producer_thread1, consumer_thread1, consumer_thread2;

    sem_init(&empty_prod, 0, 1); // setting up thread for matrices math after collection
    sem_init(&full_prod, 0, 0);
    pthread_mutex_init(&mutex_prod, NULL);

    sem_init(&empty_print, 0, 1); // setting up thread management for matrices print after math
    sem_init(&full_print, 0, 0);
    pthread_mutex_init(&mutex_print, NULL);

    // lock resources for thread 2
    sem_post(&full_prod); // increment full slots (V function)
    pthread_mutex_lock(&mutex_prod); // wait for thread resources
    sem_wait(&empty_prod); // decrement empty slots (P function)

    // lock resources for thread 3
    sem_post(&full_print); // increment full slots (V function)
    pthread_mutex_lock(&mutex_print); // wait for thread resources
    sem_wait(&empty_print); // decrement empty slots (P function)

    pthread_create(&producer_thread1, NULL, GetMatricesThread, NULL);
    pthread_create(&consumer_thread1, NULL, MultiplyMatricesThread, NULL);
    pthread_create(&consumer_thread2, NULL, PrintMatricesThread, NULL);

    pthread_join(producer_thread1, NULL); // wait for threads to finish
    pthread_join(consumer_thread1, NULL);
    pthread_join(consumer_thread2, NULL);

    sem_destroy(&empty_prod); // cleaning up thread management
    sem_destroy(&full_prod);
    pthread_mutex_destroy(&mutex_prod);
    sem_destroy(&empty_print);
    sem_destroy(&full_print);
    pthread_mutex_destroy(&mutex_print);

    return 0;
}

void* GetMatricesThread(void *args)
{
    GetMatrixSize("A", &m1Columns, &m1Rows);
    GetMatrixSize("B", &m2Columns, &m2Rows);

    if (m1Rows != m2Columns) // check if the matrices can be multiplied.
    {
        printf("Invalid matrix dimensions\n");

        // resources for MultiplyMatrices
        pthread_mutex_unlock(&mutex_prod); // release thread resources
        sem_post(&empty_prod); // increment empty slots (V function)

        return args;
    }

    matrix1 = GetMatrixWithValues("A", m1Columns, m1Rows);
    matrix2 = GetMatrixWithValues("B", m2Columns, m2Rows);

    // resources for MultiplyMatrices
    pthread_mutex_unlock(&mutex_prod); // release thread resources
    sem_post(&empty_prod); // increment empty slots (V function)
}

void* MultiplyMatricesThread(void *args)
{
    sem_post(&full_prod); // increment full slots (V function)
    pthread_mutex_lock(&mutex_prod); // wait for thread resources
    sem_wait(&empty_prod); // decrement empty slots (P function)

    if (matrix1 == NULL || matrix2 == NULL) // if the matrix is null something has gone wrong
    {
        // resources for PrintMatrices
        pthread_mutex_unlock(&mutex_print); // release thread resources
        sem_post(&empty_print); // increment empty slots (V function)

        return args;
    }

    matrix3 = Product(matrix1, matrix2, m1Columns, m1Rows, m2Columns, m2Rows, &m3Columns, &m3Rows);

    // resources for PrintMatrices
    pthread_mutex_unlock(&mutex_print); // release thread resources
    sem_post(&empty_print); // increment empty slots (V function)
}

void* PrintMatricesThread(void *args)
{
    sem_post(&full_print); // increment full slots (V function)
    pthread_mutex_lock(&mutex_print); // wait for thread resources
    sem_wait(&empty_print); // decrement empty slots (P function)

    if (matrix1 == NULL || matrix2 == NULL || matrix3 == NULL) // if the matrix is null something has gone wrong
    {
        if (matrix1 != NULL)
            free(matrix1);

        if (matrix2 != NULL)
            free(matrix2);

        if (matrix3 != NULL)
            free(matrix3);

        return args;
    }

    Print("A", matrix1, m1Rows, m1Columns);
    Print("B", matrix2, m2Rows, m2Columns);
    Print("The product of matrices A and B is", matrix3, m3Columns, m3Rows);

    free(matrix1);
    free(matrix2);
    free(matrix3);
}


// get matrix order from the user
void GetMatrixSize(char* label, int *columns, int *rows)
{
    printf("Enter the order of the matrix %s:", label);
    scanf("%d %d", columns, rows);
}

int* GetMatrixWithValues(char* label, int columns, int rows)
{
    // create dynamically sized int array;
    int *array = NewArray(rows * columns);

    printf("Enter the elements of the matrix %s:", label);
    for (int i = 0; i < columns; i++)
        for (int j = 0; j < rows; j++)
            scanf("%d", &(*(array + (rows * i) + j)));

    return array;
}

// allows me to create the matrices the size that I need.
int* NewArray(int size)
{
    return (int*)malloc(sizeof(int) * size);
}

// dumps the matrix to the console.
void Print(char *message, int *matrix, int columns, int rows)
{
    printf("%s:\n", message);
    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows; j++)
            printf("%d ", *(matrix + (rows * i) + j));

        printf("\n");
    }
}

int* Product(int *matrix1, int *matrix2, int m1Columns, int m1Rows, int m2Columns, int m2Rows, int *m3Columns, int *m3Rows)
{
    (*m3Columns) = m1Columns;
    (*m3Rows) = m2Rows;

    int *matrix3 = NewArray((*m3Columns) * (*m3Rows));

    // computers n x p matrix one * two for n x m matrix one, m x p matrix twoand stores the results in matrix3
    for(int i = 0; i < m1Columns; i++)
    {
        for(int j = 0; j < m2Rows; j++)
        {
            *(matrix3 + ((*m3Rows) * i) + j) = 0; //init the matrices
            for(int k = 0; k < m2Columns; k++)
                *(matrix3 + ((*m3Rows) * i) + j) = *(matrix3 + ((*m3Rows) * i) + j) + (*(matrix1 + (m1Rows * i) + k) * *(matrix2 + (m2Rows * k) + j)); // sum the products as you go through the matrices
        }
    }

    return matrix3;
}