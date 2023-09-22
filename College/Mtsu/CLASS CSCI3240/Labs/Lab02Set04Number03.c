/* Name: 	Timothy Beckett
 * Lab:		2
 * Set:		4
 * Number:	3
 * Description: Write a program to calculate the permutation and combination for given n and r. The
 * permutation and combination are defined for given n and r as:
 * 𝑃(𝑛𝑛, 𝑟𝑟) =  𝑛!     𝐶(𝑛, 𝑟) = 𝑃(𝑛,𝑟)
 *            (𝑛−𝑟)!               𝑟! 
 * Hint: Create two separate functions to compute permutation and combination.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>

double Factorial(double operand);
double P(double n, double r);
double C(double n, double r);

int main(int argc, char** argv)
{
    long n, r;
    
    printf("Please enter n and r\n");
    scanf("%ld %ld", &n, &r);
    
    printf("P(%ld, %ld) = %lf\nC(%ld, %ld) = %lf\n", n, r, P(n, r), n, r, C(n, r));
    
    return 0;
}

// produces the factorial value for the provided number.
double Factorial(double operand)
{
    double factorial = operand;
    
    for (int i = operand - 1; i > 0; i--)
    {
        factorial *= i;
    }
    
    return factorial;
}

// 𝑃(𝑛𝑛, 𝑟𝑟) =  𝑛!
//            (𝑛−𝑟)!
double P(double n, double r)
{
    return Factorial(n) / Factorial(n - r);
}

// 𝐶(𝑛, 𝑟) = 𝑃(𝑛,𝑟)
//            𝑟!
double C(double n, double r)
{
    return P(n, r) / Factorial(r);
}

