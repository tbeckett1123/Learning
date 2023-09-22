/* Name: 	Timothy Beckett
 * Extra Credit
 * Description: Write a program using multi-level and multi-dimension array.  Use equal amount memory
 * for both. Then using data from gprof determine which is better from a time complexity. Write a 
 * short report detailing analysis and results.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define SIZE 1000

// Structure way of tracking dynamic memory to free before ending program
struct Garbage
{
    void *Unit;
    struct Garbage *Next;
} *Head = NULL;
void AddToFinalizeList(void *unit);
void Finalize();

void InitArray(int ndArray[SIZE][SIZE], int **nMultiLevelMemory);
int Sum2DArray(int ndArray[SIZE][SIZE]);
int SumnMultiLevelMemory(int **nMultiLevelMemory);

int main(int argc, char** argv)
{
    // setup arrays for test.
    int ndArray[SIZE][SIZE];
    int **nMultiLevelMemory = (int**)malloc(sizeof(int*) * SIZE * SIZE);
    AddToFinalizeList(nMultiLevelMemory);

    for (int i = 0; i < SIZE; i++)
    {
        *(nMultiLevelMemory + i) = (int*)malloc(sizeof(int) * SIZE);
        AddToFinalizeList(*(nMultiLevelMemory + i));
    }

    sleep(500); // trying to make gmon.out generate.

    InitArray(ndArray, nMultiLevelMemory);
    Sum2DArray(ndArray);
    SumnMultiLevelMemory(nMultiLevelMemory);

    Finalize();
    exit(0); // needed for gprof
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

void InitArray(int ndArray[SIZE][SIZE], int **nMultiLevelMemory)
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
        {
            // using same values to help prevent any data bias that could affect the results.
            ndArray[i][j] = *(*(nMultiLevelMemory + i) + j) = i + j + 1;
        }
}

int Sum2DArray(int ndArray[SIZE][SIZE])
{
    clock_t start_block1 = clock(); // clocking execution time.

    int sum = 0;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            sum += ndArray[i][j];

    clock_t end_block1 = clock(); // clocking execution time.

    double elapsed_time_block1 = (double)(end_block1 - start_block1) / CLOCKS_PER_SEC;
    printf("Sum2DArray execution time: %lf seconds\n", elapsed_time_block1);

    return sum;
}

int SumnMultiLevelMemory(int **nMultiLevelMemory)
{
    clock_t start_block1 = clock(); // clocking execution time.

    int sum = 0;
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                sum += *(*(nMultiLevelMemory + i) + j);

    clock_t end_block1 = clock(); // clocking execution time.

    double elapsed_time_block1 = (double)(end_block1 - start_block1) / CLOCKS_PER_SEC;
    printf("SumnMultiLevelMemory execution time: %lf seconds\n", elapsed_time_block1);

    return sum;
}
