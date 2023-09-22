/* Name: 	Timothy Beckett
 * Lab:		2
 * Set:		3
 * Number:	3
 * Description: Write a program to display the given sequence up to the n th term.
 * 1, 2, 5, 10, 17, 26 ..... n th term.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>

int main(int argc, char** argv)
{
    int input;
    
    // get the n term
    printf("Please enter Nth term to display.\n");
    scanf("%d", &input);
    
    // calculate Sigma(i^2 + 1) i = 0 to n
    for (int i = 0; i < input; i++)
    {        
        printf("%d ", (i * i) + 1);
    }
    
    puts("\n");
        
    return 0;
}