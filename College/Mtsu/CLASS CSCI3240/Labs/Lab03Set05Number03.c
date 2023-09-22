/* Name: 	Timothy Beckett
 * Lab:		3
 * Set:		5
 * Number:	3
 * Description: Write a function mergeArrays that takes two integer arrays (arr1 and arr2) along
 * with their sizes (size1 and size2) as arguments. The function should perform the
 * following steps:
 *  a. Concatenate the elements of arr1 and arr2 into a new array called result,
 *     maintaining the order of elements.
 *  b. Remove any duplicate elements from the result array.
 *  c. Sort the elements of the result array in ascending order.
 *  d. Return the result array to the main function.
 *  e. Your task is to implement the mergeArrays function and write a main function
 *     to test it.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int GetArraySize();
int* GetArrayWithValues(int size);
int* MergeArrays(int *array1, int *array2, int size1, int size2, int *resultSize);
int* NewArray(int size);
int* Concat(int *array1, int *array2, int size1, int size2);
int* RemoveDuplicates(int *array, int *size);
void Sort(int *array, int size);
void PrintArray(int *array, int n);

int main(int argc, char** argv)
{
    int *array1, *array2, *array3, size1, size2, size3;

    size1 = GetArraySize();
    array1 = GetArrayWithValues(size1);
    
    size2 = GetArraySize();
    array2 = GetArrayWithValues(size2);
    
    array3 = MergeArrays(array1, array2, size1, size2, &size3);
    
    PrintArray(array3, size3);
    
	 free(array1);
	 free(array2);
	 free(array3);
	
    return 0;
}

// gets the array size from the user.
int GetArraySize()
{
    int n;
    
    printf("Please enter the number of items in the array:\n");
    scanf("%d", &n);
    
    return n;
}

// creates an array and gets the values from the user
int* GetArrayWithValues(int size)
{
    // create dynamically sized int array;
    int *array = NewArray(size);     
    
    printf("Please enter %d numbers:\n", size);
    for (int i = 0; i < size; i++)
        scanf("%d", &array[i]);
    
    return array;
}

// combines the 2 arrays and removes the duplicates
int* MergeArrays(int *array1, int *array2, int size1, int size2, int *resultSize)
{
    int *result = Concat(array1, array2, size1, size2);
    (*resultSize) = size1 + size2;

    Sort(result, *resultSize);
    int *result1 = RemoveDuplicates(result, resultSize);
 
	free(result);
 
    return result1;
}

//Creates memory for an array the size that you need.
int* NewArray(int size)
{
    return (int*)malloc(sizeof(int) * size);
}

//combines 2 arrays.
int* Concat(int *array1, int *array2, int size1, int size2)
{
    int i = 0, *result = NewArray(size1 + size2);
        
    for (int j = 0; j < size1; j++, i++)
        result[i] = array1[j];

    for (int j = 0; j < size2; j++, i++)
        result[i] = array2[j];   
    
    return result;
}

// creates an array with unique values.
int* RemoveDuplicates(int *array, int *size)
{
    int *temp = NewArray(*size), n, loc;
    bool isDup;
    
    // priming the new array with first element.
    temp[0] = array[0];
    n = 1;
    loc = 1;
    
    for (int i = 1; i < *size; i++)
    {
        isDup = false;
        
        //search for value in array
        for (int j = 0; j < n && !isDup; j++)
            isDup = temp[j] == array[i];
        
        //add value to new array if not in array
        if (!isDup)
        {
            temp[loc] = array[i];
            loc++;
            n++;
        }
    }
        
    (*size) = n;
    
    return temp;    
}

// sorts the array
void Sort(int *array, int size)
{
    int min, temp;
    
    // One by one move boundary of unsorted subarray
    for (int i = 0; i < size-1; i++)
    {
        // Find the minimum element in unsorted array
        min = i;
        for (int j = i+1; j < size; j++)
          if (array[j] < array[min])
            min = j;
  
        // Swap the found minimum element with the first element        
        temp = array[min];
        array[min] = array[i];
        array[i] = temp;
    }
}

// dump the array values to the console
void PrintArray(int* array, int n)
{
    for(int i = 0; i < n; i++)
        printf("%d ", array[i]);
    
    printf("\n");
}