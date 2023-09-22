/* Name: 	Timothy Beckett
 * Lab:		10
 * Number:	1
 * Description: Write a program that uses the fork system call to create a child process that
 * prints "Hello, world!" to the console. The parent process should wait for the
 * child process to finish before terminating.
 */

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    printf("I am: %d\n", (int)getpid()); // just displaying the process id

    pid_t pid = fork(); // having a baby!

    if (pid == 0) // child process code
    {
        printf("Hello World!\n");
        exit(0);
    }
    else // parent process code
    {
        printf("Waiting on child process to complete.\n"); // telling the user what's up
        wait(NULL); // waiting for the child process to complete
        printf("Goodbye World!\n");
    }

    return 0;
}