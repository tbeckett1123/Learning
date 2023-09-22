/* Name: 	Timothy Beckett
 * Lab:		10
 * Number:	3
 * Description: Write a program that uses the fork system call to create two child processes
 * that each print a message to the console. The parent process should wait for
 * both child processes to finish before terminating.
 */

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

unsigned int Factorial(unsigned int operand);

int main(int argc, char **argv)
{
    printf("parent process spinning up...\n"); // just displaying the process

    pid_t child1;

    child1 = fork(); // having a baby!

    if (child1 == 0) // child process code
    {
        unsigned int i;

        printf("Enter an integer: ");
        scanf("%u", &i);

        printf("The factorial of %u is %u\n", i, Factorial(i));

        exit(0);
    }
    else // parent process code
    {
        printf("Waiting on child processes to complete.\n"); // telling the user what's up

        waitpid(child1, NULL, 0); // waiting for child processes to complete

        printf("Goodbye World!\n");
    }

    return 0;
}

// F = n!
unsigned int Factorial(unsigned int operand)
{
    unsigned int factorial = operand;

    for (int i = operand - 1; i > 0; i--)
    {
        factorial *= i;
    }

    return factorial;
}