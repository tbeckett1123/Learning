/* Name: 	Timothy Beckett
 * Lab:		3
 * Set:		5
 * Number:	1
 * Description: Write a program to read ‘n’ numbers and sort them in ascending order. Display the
 * content of the array before and after the sorting operation is performed.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <stdlib.h>

void PrintArray(int *array, int n);

int main(int argc, char** argv)
{
    int *array, n, input, i, j, min, temp;

    printf("Please enter the number of items to be sorted:\n");
    scanf("%d", &n);
    
    // create dynamically sized int array;
    array = (int*)malloc(sizeof(int) * n); 
    
    printf("Please enter %d numbers:\n", n);
    for(i = 0; i < n; i++)
        scanf("%d", &array[i]);
    
    PrintArray(array, n);
    
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++)
    {
        // Find the minimum element in unsorted array
        min = i;
        for (j = i+1; j < n; j++)
          if (array[j] < array[min])
            min = j;
  
        // Swap the found minimum element with the first element        
        temp = array[min];
        array[min] = array[i];
        array[i] = temp;
    }
    
    PrintArray(array, n);
    
    return 0;
}

// Print the array.
// n is the size of the array.
void PrintArray(int* array, int n)
{
    for(int i = 0; i < n; i++)
        printf("%d ", array[i]);
    
    printf("\n");
}