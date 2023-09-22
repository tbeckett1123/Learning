/* Name: 	Timothy Beckett
 * Lab:		2
 * Set:		4
 * Number:	1
 * Description: Write a program to create a user-defined function named “factorial” that finds the
 * factorial of a number entered by the user. The factorial function should take only
 * one argument. The result should be displayed from the main function
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>

unsigned long Factorial(unsigned long operand);

int main(int argc, char** argv)
{
    unsigned long operand, factorial;
    
    // get the number from the user
    printf("Please enter an integer number\n");
    scanf("%lu", &operand);
    
    // calculate the factorial
    factorial = Factorial(operand);
    
    // display the results.
    printf("The factorial of %lu is %lu.\n", operand, factorial);

    return 0;
}

// F = n!
unsigned long Factorial(unsigned long operand)
{
    unsigned long factorial = operand;
    
    for (int i = operand - 1; i > 0; i--)
    {
        factorial *= i;
    }
    
    return factorial;
}