/* Name: 	Timothy Beckett
 * Lab:		4
 * Set:		7
 * Number:	1
 * Description: Write a program to read the characters from the user until the user enters comma
 * character (,) and stores it in a file.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
# include <stdio.h>
# include <string.h>
# define TEXT_SIZE 1024


int main(int argc, char** argv)
{   
    // give the user the option to provide a filename or use the default.
    char *filename = argc > 1 ? *(argv+1) : "Lab04Set07Number01Output.txt";
    char text[TEXT_SIZE];
    FILE *fptr;
    
    // initialize the array to nulls for baseline
    bzero(text, TEXT_SIZE);
    
    // opening the file pointer to write mode.
    if ((fptr = fopen(filename, "w")) == NULL)    
    {
        printf("Error opening file\n");
        
        return 1;
    }
    
    
    //get user input until they enter a comma
    while(scanf("%1024[^,]s", text))
    {
        //write text to file
        fprintf(fptr, "%s", text);
        
        // initialize the array to nulls for baseline
        bzero(text, TEXT_SIZE);
    }

    // closing the file pointer
    fclose(fptr);
    
    return 0;
}
