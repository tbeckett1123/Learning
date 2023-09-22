/* Name: 	Timothy Beckett
 * Lab:		1
 * Set:		2
 * Number:	1
 * Description: Write a program to read a positive integer n and check whether it is odd or even. Use
 * the Switch statement.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>

int main(int argc, char** argv)
{
    int input;
    char* itIs;

    // get a number from the user
    printf("Please enter an integer:\n");
    scanf("%d", &input);

    // if the number is evenly divisable by 2 then it is even.
    switch(input % 2)
    {
        case 0:
            itIs = "even";
            break;
        default:
            itIs = "odd";
    }

    printf("%d is %s\n", input, itIs);
    
    return 0;
}