/* Name: 	Timothy Beckett
 * Lab:		2
 * Set:		3
 * Number:	1
 * Description: Write a program to take positive integers as input until 0 is entered and compute the
 * average of even numbers entered by the user.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>

int main(int argc, char** argv)
{
    int sum = 0, count = 0, input;
    float average;
    
    // get values from the user and keep getting input till zero is entered
    printf("Enter positive integer numbers.\n");
    printf("Enter 0 (zero) to stop entering numbers.\n");
    
    do
    {
        scanf("%d", &input);
        
        if (input > 0 && input % 2 == 0)
        {
            sum += input;
            count++;
        }
        
    }while(input != 0);
    
    // calculate the average.
    if (count > 0)
    {
        average = (float)sum / (float)count;
        
        printf("The average of the positive even integers entered is %f.\n", average);
    }
    else
    {
        printf("There were no positive even integers entered.\n");
    }
    
    return 0;
}