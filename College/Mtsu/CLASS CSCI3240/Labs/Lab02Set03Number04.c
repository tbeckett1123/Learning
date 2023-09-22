/* Name: 	Timothy Beckett
 * Lab:		2
 * Set:		3
 * Number:	4
 * Description: Write a program to compute the sum of the given series up to the nth term.
 * 1 – x^2 + x^4 – x^6 + x^8 - ......... n th term.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <math.h>

int main(int argc, char** argv)
{
    int n, sum = 1, exponent = 2, sign = -1;
    
    printf("Please enter nth position to calculate to:\n");
    scanf("%d", &n);
      
    // the instructions did not specify so I assumed that x shoudl start at 0.
    for(int i = 0; i < n; i++)
    {
        // note this is limited to the space of an int. due to the exponent doubling and overflow could occur quickly.
        sum += sign * pow(i, exponent);
        sign *= -1;
        exponent += 2;
    }
    
    printf("The sum to %d th place is %d\n", n, sum);
    
    return 0;
}