/* Name: 	Timothy Beckett
 * Lab:		10
 * Number:	2
 * Description: Write a program that uses the fork system call to create two child processes
 * that each print a message to the console. The parent process should wait for
 * both child processes to finish before terminating.
 */

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    printf("parent process spinning up...\n"); // just displaying the process

    pid_t child1, child2;

    child1 = fork(); // having a baby!

    if (child1 == 0) // child process code
    {
        printf("Hello World!\nprocess id is %d\n", (int)getpid());
        exit(0);
    }
    else // parent process code
    {
        child2 = fork(); // having a baby!
        if (child2 == 0) // child process code
        {
            printf("Hello World!\nprocess id is %d\n", (int)getpid());
            exit(0);
        }
        else
        {
            printf("Waiting on child processes to complete.\n"); // telling the user what's up

            waitpid(child1, NULL, 0); // waiting for child processes to complete
            waitpid(child2, NULL, 0);

            printf("Goodbye World!\n");
        }
    }

    return 0;
}