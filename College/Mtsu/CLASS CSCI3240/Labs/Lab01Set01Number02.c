/* Name: 	Timothy Beckett
 * Lab:		1
 * Set:		1
 * Number:	2
 * Description: Write a program to accept Fahrenheit temperature and convert it to degrees Celsius.
 * Hint: F = (C*9/5) + 32
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
int main(int argc, char** argv)
{    
    float fahrenheit, celsius;
    
    // get the temperature in F from the user.
    printf("Please enter a temprature in Fahrenheit:\n");
    scanf("%f", &fahrenheit);

    // calulate C
    celsius = (5.0f * fahrenheit - 160.0f) / 9.0f; 
    
    printf("%f Fahrenheit is %f celsius\n", fahrenheit, celsius);
    
    return 0;
}