/* Name: 	Timothy Beckett
 * Lab:		4
 * Set:		7
 * Number:	2
 * Description: Write a program to read a file character by character and store it in an array of strings.
 * If the array is full, print it (with a newline). Then, continue to store the next set of
 * characters. You can set the size of the array to 10. In case of the end of the file (eof),
 * print the array with a newline character and exit. Your program should get the
 * filename as a command line argument.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
# include <stdio.h>
# include <string.h>
# define TEXT_SIZE 10


int main(int argc, char** argv)
{   
    // check for filename.
    if (2 < argc)
    {
        printf("Filename not found\n");
        return 1;
    }
    
    char *filename =  *(argv+1);
    char text[TEXT_SIZE];        
    FILE *fptr;
    
    // initialize the array to nulls for baseline
    bzero(text, TEXT_SIZE);
    
    // opening the file pointer to write mode.
    if ((fptr = fopen(filename, "r")) == NULL)    
    {
        printf("Error opening file\n");
        
        return 1;
    }
    
    
    // read from the file until you get to eof
    // print every 10 characters to a new line
    while(fgets(text, TEXT_SIZE, fptr) != NULL)
    {
        // write text to file
        printf( "%s\n", text);
        
        // reset the array to nulls for baseline
        bzero(text, TEXT_SIZE);
    }

    if (strlen(text) > 0)
        printf("%s\n", text);
    
    // closing the file pointer
    fclose(fptr);
    
    return 0;
}
