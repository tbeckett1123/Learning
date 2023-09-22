/* Name: 	Timothy Beckett
 * Lab:		7
 * Set:		10
 * Number:	4
 * Description: Using pointers, write a program to find out the largest and the smallest among five
 * numbers.
 */
#include <stdio.h>

#define SIZE 5

void Max(int values[], int *max);
void Min(int values[], int *min);

int main()
{
    int values[SIZE], max, min, *itr, i;

    // setup interator.
    itr = values;
    printf("Enter 5 numbers: ");
    for (i = 0; i < SIZE; i++)
        scanf("%d", (itr++));

    Max(values, &max);
    Min(values, &min);

    printf("The max is %d\nThe min is %d\n", max, min);

    return 0;
}

void Max(int values[], int *max)
{
    *max = values[0]; // set inital value.

    // iterate through the rest of the array looking for a new max.
    for (int i = 1; i < SIZE; i++)
    {
        if (*max < values[i]) // find a new max and set it.
            *max = values[i];
    }
}

void Min(int values[], int *min)
{
    *min = values[0]; // set inital value.

    // iterate through the rest of the array looking for a new min.
    for (int i = 1; i < SIZE; i++)
    {
        if (*min > values[i]) // find a new min and set it.
            *min = values[i];
    }
}
