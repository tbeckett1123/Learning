/* Name: 	Timothy Beckett
 * Lab:		1
 * Set:		1
 * Number:	1
 * Description: Write a program to display the ASCII value of a given character.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>

int main(int argc, char** argv)
{
    char input;
    
    // get a charater from the user and display it's ASCII hex code.
    printf("Please enter a charater:\n");
    scanf("%c", &input);
    
    printf("%X", input);
    
    return 0;
}