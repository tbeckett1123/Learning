/* Name: 	Timothy Beckett
 * Lab:		10
 * Number:	4
 * Description: Write a program that uses the fork system call to create a child process that
 * reads a string from the console and converts it to uppercase. The child
 * process should then print the uppercase string to the console, and the parent
 * process should wait for the child process to finish before terminating.
 */

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char* ToUpperCase(char *string);

int main(int argc, char **argv)
{
    printf("parent process spinning up...\n"); // just displaying the process

    if (argc < 3)
    {
        fprintf(stderr, "usage: ./Lab10Number04 Enter a test string here.\n");
        return 1;
    }

    pid_t child1;

    child1 = fork(); // having a baby!

    if (child1 == 0) // child process code
    {
        char *string;

        for (int i = 1; i < argc; i++)
        {
            string = ToUpperCase(argv[i]);  // convert to upper case and print
            printf("%s ", string);
            free(string); // free up the string created.
        }

        printf("\n");
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

// turns string to uppper case letters
char* ToUpperCase(char *string)
{
    int l = strlen(string); // get the length of the original string
    char *uString = (char*)malloc(sizeof(char) * l + 1); // create char array for the new string

    bzero(uString, l); // initialize the char array to nulls

    for (int i = 0; i < l; i++)
        uString[i] = toupper(string[i]);  // convert the alpha characters to upper case

    uString[l] = '\0'; // null terminate the string.

    return uString;
}