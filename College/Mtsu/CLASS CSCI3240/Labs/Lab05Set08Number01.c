/* Name: 	Timothy Beckett
 * Lab:		5
 * Set:		8
 * Number:	1
 * Description: Create a structure Length to store length in feet & inches. Your program should read
 * two Lengths and display their sum and difference.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
# include <stdio.h>

struct Length
{
    unsigned int Feet;
    unsigned int Inches;
};

void GetLength(char *message, struct Length *operand);
void Sum(struct Length operand1, struct Length operand2);
void Difference(struct Length operand1, struct Length operand2);

int main(int argc, char** argv)
{   
    struct Length operand1;
    struct Length operand2;
    
    GetLength("first", &operand1);  // get the first length
    GetLength("second", &operand2); // get the second length
    
    Sum(operand1, operand2);
    Difference(operand1, operand2);
    
    return 0;
}

void GetLength(char *message, struct Length *operand)
{
    printf("Enter the %s length in feet and inches. (enter 0 for feet or inches to skip)\n", message);
    scanf("%u %u", &(operand->Feet), &(operand->Inches));
}

void Sum(struct Length operand1, struct Length operand2)
{
    //convert the lengths inches
    unsigned int op1 = operand1.Feet * 12 + operand1.Inches, op2 = operand2.Feet * 12 + operand2.Inches;
    
    long total = op1 + op2;   // sum the lengths
    long inches = total % 12; // calculate the inches in the total
    long feet = total / 12;   // calculate the feet in the total    
    
    printf("The sum of %u' %u\" and %u' %u\" is %ld' %ld\"\n", operand1.Feet, operand1.Inches, operand2.Feet, operand2.Inches, feet, inches);
}

void Difference(struct Length operand1, struct Length operand2)
{
    //convert inches to feet and inches
    unsigned int op1 = operand1.Feet * 12 + operand1.Inches, op2 = operand2.Feet * 12 + operand2.Inches;
    
    //swap the values if need
    if (op1 < op2)    
    {
        op2 = op2^op1;
        op1 = op2^op1;
        op2 = op2^op1;
    }
    
    long total = op1 - op2;   // find the difference of the lengths
    long inches = total % 12; // calculate the inches in the total
    long feet = total / 12;   // calculate the feet in the total    
    
    printf("The difference of %u' %u\" and %u' %u\" is %ld' %ld\"\n", operand1.Feet, operand1.Inches, operand2.Feet, operand2.Inches, feet, inches);
}