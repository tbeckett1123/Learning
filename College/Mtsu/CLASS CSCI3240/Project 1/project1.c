/* Name:    Timothy Beckett
 * Project: 1
 * Description: Write a C program that takes a single command-line argument and produces the same output as the xxd   
 * program withthe same argument. You must include meaningful comments on your code. You must name your program file as 
 * project1.c. 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <ctype.h>

int offset[16] = { 30, 28, 26, 24, 22, 20, 18, 16, 14, 12, 10, 8, 6, 4, 2, 0 };

void InitArray(int size, char* buffer);

int main(int argc, char** argv)
{
    // Note that the first element in argv is "./Project1".  The file name will be in the 2nd element.
        
    char input;    
    char output[17];
    FILE* filePtr;
    int line = 0, // line counter.
    spacer = 0,   // tracking spaces for hex dump.    
    count = 0;    // tracking the character count for the line.
        
    filePtr = fopen(argv[1], "r");
    
    InitArray(17, output);
    
    // print 1st line line number.
    printf("%07x0: ", line);
    
    // read characters till the end of the file. 
    while(fscanf(filePtr, "%c", &input) != EOF)
    {
        
        output[count] = input;
        count++;
        
        // handling line feeds
        if (input == 10) 
        {
            output[count - 1] = '.';
            printf("0a");
        }
        // check if printable character.
        else if (!isprint(input))
        {
            printf(".");
        }                
        else
        {
            printf("%x", input);
        }
        
        // print a space every 2nd character.
        spacer = (spacer + 1) % 2;
            
        if (spacer == 0)
            printf(" ");
        
        // dump the buffer and advance to a new line very 16th character.
        if (count == 16)
        {
            line++;
            printf(" %s\n%07x0: ", output, line);
            count = 0;            
            InitArray(17, output);
        }        
    }
    
    if (count < 16)
    {        

        // print place holders to maintain formatting        
        for (int i = offset[count - 1]; i > 0; i--)
            printf(" ");
             
        printf("   %s\n", output);        
    }
        
    fclose(filePtr);
    
    return 0;
}

void InitArray(int size, char* buffer)
{
    for (int i = 0; i < size; i++)
        buffer[i] = '\0';
}