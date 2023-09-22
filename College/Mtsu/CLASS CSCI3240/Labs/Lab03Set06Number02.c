/* Name: 	Timothy Beckett
 * Lab:		3
 * Set:		6
 * Number:	2
 * Description: Write a program to read a line of text from the user. Your program should count the
 * number of words. For each word, if the word starts with a vowel, capitalize, and
 * display them in ascending order.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void GetText(char *text);
void Split(char *text, char *words[], int *wordCnt);
void Find(char *words[], char *words2[], int *vowels, int wordCnt);
void Sort(char *words2[], int vowels);
int Greater(char *one, char *two);
void Print(char *arr[], int length, int wordCnt);

char vowel[] = "aeiouy";

int main(int argc, char** argv)
{    
    char text[5050], *words[100], *words2[100];    
    int wordCnt, vowels;
    
    GetText(text);    
    Split(text, words, &wordCnt);
    Find(words, words2, &vowels, wordCnt);    
    Sort(words2, vowels);    
    Print(words2, vowels, wordCnt);
        
    return 0;
}

void GetText(char *text)
{
    printf("Enter test:");
    scanf("%5050[^\n]s", text);
}

void Split(char *text, char *words[], int *wordCnt)
{
    char *token;
    *wordCnt = 0;
    
    // split the string by space.
    token = strtok(text, " ");    
    while(token != NULL && *wordCnt < 100)
    {   
        words[*wordCnt] = token;
        
        (*wordCnt)++;
        token = strtok(NULL, " ");
    }
}

void Find(char *words[], char *words2[], int *vowels, int wordCnt)
{
    int isVowel, length, i, j, k;
    
    // find the words that starts with vowels.
    for (i = 0; i < wordCnt; i++)
    {
        isVowel = 0;
        for (j = 0; j < 6; j++)
        {            
            if (tolower(words[i][0]) == vowel[j])
                isVowel = 1;
        }
        
        if (isVowel)
        {
            words2[*vowels] = words[i];
            
            length = strlen(words2[*vowels]);
            
            // upper case all letters and assign to sorting array.
            for(k = 0; k < length; k++)
                words2[*vowels][k] = toupper(words2[*vowels][k]);
            
            (*vowels)++;
        }            
    }
}

// Returns 1 for one greater than two
// Returns 0 for one equal to two
// Retuns -1 for one less than two
int Greater(char *one, char *two)
{        
    int	oneLen = strlen(one),
		twoLen = strlen(two), 
		greater = 0,
		size, i, j;    
    
    // only look at the size of the smaller array.
    oneLen > twoLen ? twoLen : oneLen;
    
    for (i = 0, j = 0; i < size - 1; i++, j++)
    {
        if (one[i] < two[j])
        {
            greater = -1;
            j = i = size;
        }
        else if(one[i] > two[j])
        {
            greater = 1;
            j = i = size;
        }        
    }
    
    return greater;
}

void Sort(char *words2[], int vowels)
{
    int i, j, min;
    char *temp;
    
    // One by one move boundary of unsorted subarray
    for (i = 0; i < vowels-1; i++)
    {
        // Find the minimum element in unsorted array
        min = i;
        for (j = i+1; j < vowels; j++)
          if (Greater(words2[j], words2[min]) < 0)
            min = j;
  
        // Swap the found minimum element with the first element        
        temp = words2[min];
        words2[min] = words2[i];
        words2[i] = temp;
    }
}

void Print(char *arr[], int length, int wordCnt)
{
    printf("There are %d words.\n", wordCnt);
    printf("Words starting with a vowel in ascending order:\n");
    for (int i = 0; i < length; i++)
        printf("%s\n", arr[i]);
}