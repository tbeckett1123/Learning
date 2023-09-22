/* Name: 	Timothy Beckett
 * Lab:		3
 * Set:		6
 * Number:	1
 * Description: Write a program to read a line of text from the user. Your program should display the
 * count of vowels, consonants, white spaces, digits, and special characters in it. Use a
 * character array to store the line.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char** argv)
{
    char vowel[] = "aeiouy";
    char text[2048];
    int textSize = 0, vowels = 0, consonants = 0,  whiteSpaces = 0, digits = 0, specialCharacters = 0;
    
    printf("Enter some text for evaluation:\n");
    scanf("%2048[^\n]s", text);
    
    textSize = strlen(text);
    
    for(int i = 0; i < textSize; i++)
    {
        // tally the characters by character type.
        if (isdigit(text[i]))
        {
            digits++;
        }
        else if (isspace(text[i]))
        {
            whiteSpaces++;
        }
        else if (isalpha(text[i]))
        {
            int j = 0; 
            for (j = 0; j < 6; j++)
            {
                // if it's a vowel breakout;
                if (tolower(text[i]) == vowel[j])
                    j = 7;
            }
            
            // if j is 6 then the letter is a consonant, any other value for j means the letter is a vowel.
            if (j == 6)
                consonants++;
            else
                vowels++;
        }
        else
        {
            specialCharacters++;
        }
    }
    
    printf("vowels = %d\nconsonants = %d\nwhite spaces = %d\ndigits = %d\nspecial characters = %d\n", vowels, consonants, whiteSpaces, digits, specialCharacters);
        
    return 0;
}

