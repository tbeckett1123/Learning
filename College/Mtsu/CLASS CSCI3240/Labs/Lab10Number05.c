/* Name: 	Timothy Beckett
 * Lab:		10
 * Number:	5
 * Description: Write a program that uses the fork system call to create a child process that
 * reads a list of integers from the console and finds the sum of the even
 * numbers. The child process should then print the result to the console, and
 * the parent process should wait for the child process to finish before
 * terminating.
 */

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char **argv)
{
    printf("parent process spinning up...\n"); // just displaying the process

    if (argc < 3)
    {
        fprintf(stderr, "usage: ./Lab10Number05 1 2 3 4 5\n");
        return 1;
    }

    pid_t child1;

    child1 = fork(); // having a baby!

    if (child1 == 0) // child process code
    {
        char *string;
        int tally = 0, n;

        printf("The sum of the even numbers is ");

        for (int i = 1; i < argc; i++)
        {
            n = atoi(argv[i]); // convert the text to number.

            if (n % 2 == 0) // if n mod 2 == 0 then the number is even
                tally += n;
        }

        printf("%d\n", tally);
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