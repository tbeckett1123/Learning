/* Name: 	Timothy Beckett
 * Lab:		1
 * Set:		1
 * Number:	3
 * Description: Write a program to read the radius of a circle and compute its area and
 * circumference. Use symbolic constants to define the value of the pie.
 * Hint: #define PIE 3.1416
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#define PIE 3.1416


int main(int argc, char** argv)
{    
    float radius, area;
    
    // determine the area of a circle.
    printf("Please enter the radius of a circle:\n");
    scanf("%f", &radius);
  
    area = PIE * radius * radius; 
    
    printf("The area of a circle with the radius %f is %f \n", radius, area);
    
    return 0;
}