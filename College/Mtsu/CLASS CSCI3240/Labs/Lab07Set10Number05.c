/* Name: 	Timothy Beckett
 * Lab:		7
 * Set:		10
 * Number:	5
 * Description: Using pointers, write a program to count vowels and consonants in a string.
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main()
{
    char vowel[] = "aeiouy";
    char text[2048];
    int textSize = 0, vowels = 0, consonants = 0, *vptr, *cptr;

    vptr = &vowels;
    cptr = &consonants;

    printf("Enter some text for evaluation:\n");
    scanf("%2048[^\n]s", text);

    textSize = strlen(text);

    for(int i = 0; i < textSize; i++)
    {
        // tally the characters by character type.
        if (isalpha(*(text + i)))
        {
            int j = 0;
            for (j = 0; j < 6; j++)
            {
                // if it's a vowel breakout;
                if (tolower(*(text + i)) == *(vowel + j))
                    j = 7;
            }

            // if j is 6 then the letter is a consonant, any other value for j means the letter is a vowel.
            if (j == 6)
                (*cptr)++;
            else
                (*vptr)++;
        }
    }

    printf("vowels = %d\nconsonants = %d\n", vowels, consonants);

    return 0;
}