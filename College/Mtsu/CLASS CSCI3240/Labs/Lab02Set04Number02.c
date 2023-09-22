/* Name: 	Timothy Beckett
 * Lab:		2
 * Set:		4
 * Number:	2
 * Description: Write a program to create two user-defined functions that take arguments to find the
 * area of the rectangle and circle. The result should be displayed from the main
 * function.
 * Hint: rectangle function requires two arguments (length & width) and circle
 * function requires only one argument: radius.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI acos(-1)

double AreaOfRectangle(double length, double width);
double AreaOfCircle(double radius);
void GetOperandsFromUserInput(char* userInput, double operands[], int* count);

int main(int argc, char** argv)
{
    char userInput[1024];
    double operands[] = { 0, 0 };
    int count;
    double area;
    
    // get the values from the user and parse it for a to be determined
    printf("Please enter either the length and width, seperated by a space, of a rectangle or the radius of a circle to get the area\n");
    scanf("%1023[^\n]", userInput);
    
    GetOperandsFromUserInput(userInput, operands, &count);

    // calculate the area of the geometric shape
    switch(count)
    {
         case 1:             
             area = AreaOfCircle(operands[0]);
             printf("The area of a circle with the radius %lf is %lf\n", operands[0], area);
             break;
         case 2:             
             area = AreaOfRectangle(operands[0], operands[1]);
             printf("The area of a rectangle %lf x %lf is %lf\n", operands[0], operands[1], area);
             break;
    }
 
    return 0;
}

// gets the values from the user input and puts it in an array.
void GetOperandsFromUserInput(char* userInput, double operands[], int* count)
{       
    char* token;

    (*count) = 0;
    
    token = strtok(userInput, " ");    
    while(token != NULL)
    {   
        operands[*count] = atof(token);
        
        (*count)++;
        token = strtok(NULL, " ");
    }    
}

// A = l * w
double AreaOfRectangle(double length, double width)
{
    return length * width;
}

// A = P * r^2
double AreaOfCircle(double radius)
{
    return PI * (radius * radius);
}