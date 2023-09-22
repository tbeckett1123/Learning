/* Name: 	Timothy Beckett
 * Lab:		8
 * Set:		11
 * Number:	4
 * Description: Write a program to perform the following tasks:
 *   a. Read a file (the name of the file should be sent as a command-line argument)
 *   b. The first line of the file specifies the total number of students in a classroom.
 *   c. Each line after the first line holds the exam score for individual students.
 *   d. Your program should read the first line to get the total number of students and
 *      dynamically allocate memory to hold the exam score for all the students.
 *   e. Sort the exam scores in ascending order.
 *   f. Finally, print them in one single line (separated by commas)
 *
 * Example:
 * Sample input text 1:
 * scoresheet1.txt
 * 7
 * 97.25
 * 56.50
 * 88.75
 * 21.50
 * 73.00
 * 33.75
 * 85.50
 *
 * Sample Output:
 * ./problem4 scoresheet1.txt
 * 21.50,33.75,56.50,73.00,85.50,88.75,97.25
 */
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv)
{
    if (2 < argc) // check for filename
    {
        fprintf(stderr, "The filename is required.\n");
        return 1;
    }

    char *filename =  *(argv+1);
    int count;
    double *numbers;
    FILE *fptr;

    if ((fptr = fopen(filename, "r")) == NULL) // opening the file pointer to read mode
    {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }

    fscanf(fptr, "%d", &count); // get record count

    if (count > 0)
    {
        numbers = (double*)malloc(sizeof(double) * count); // allocate array memory

        for (int i = 0; i < count; i++)
            fscanf(fptr, "%lf", (numbers + i));

        printf("%lf", *(numbers)); // primer print for commas

        for (int i = 1; i < count; i++) // print remaining numbers
            printf(",%lf", *(numbers + i));

        printf("\n");
        free(numbers); // clean up array
    }

    fclose(fptr); // closing the file pointer

    return 0;
}