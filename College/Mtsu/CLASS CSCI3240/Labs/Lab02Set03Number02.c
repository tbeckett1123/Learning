/* Name: 	Timothy Beckett
 * Lab:		2
 * Set:		3
 * Number:	2
 * Description: Write a program to check whether a number is triangular.
 * Example: 3 =1+2; 6 = 1+2+3, 10 = 1+2+3+4, ...
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*
Methodology: Triangular numbers run in sets.
T1 = 1 next 1 + 2, 
T2 = 3 next 3 + 3, 
T3 = 6 next 6 + 4, ...
*/

#include <stdio.h>
#include <stdbool.h>

int main(int argc, char** argv)
{
    unsigned long int t = 1, adder = 2, input;
    bool isTriangular = false;
    
    // get the input from the user.
    printf("Please enter a number to be evaluated if it is a triangular number\n");
    scanf("%lu", &input);
    
    // determine if the values are triangular
    do
    {
        isTriangular = t == input;
        t += adder;
        adder++;
    }while(t <= input);
    
    printf("%lu is%sa triangular number.\n", input, (isTriangular ? " " : " not "));
        
    return 0;
}