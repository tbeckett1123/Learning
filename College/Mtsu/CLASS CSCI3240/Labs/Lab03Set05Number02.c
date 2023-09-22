/* Name: 	Timothy Beckett
 * Lab:		3
 * Set:		5
 * Number:	2
 * Description: Write a program to read the numbers in an array and reverse the order of the elements.
 * Display the content of the array before and after the reverse operation is performed.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <stdlib.h>

void PrintArray(int *array, int n);

int main(int argc, char** argv)
{
    int *array, *temp, n, input;

    printf("Please enter the number of items to be sorted:\n");
    scanf("%d", &n);
    
    // create dynamically sized int array;
    array = (int*)malloc(sizeof(int) * n); 
    temp = (int*)malloc(sizeof(int) * n); 
    
    printf("Please enter %d numbers:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &array[i]);
    
    PrintArray(array, n);
    
    // copy array for reverse
    for (int i = 0; i < n; i++)
        temp[i] = array[i];
    
    // reverse the values in the array
    for (int i = n - 1, j = 0; i > -1; i--, j++)        
        array[j] = temp[i];
    
    PrintArray(array, n);
    
    return 0;
}

// dumps the array to the console
void PrintArray(int* array, int n)
{
    for(int i = 0; i < n; i++)
        printf("%d ", array[i]);
    
    printf("\n");
}