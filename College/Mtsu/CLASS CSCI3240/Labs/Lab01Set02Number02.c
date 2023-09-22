/* Name: 	Timothy Beckett
 * Lab:		1
 * Set:		2
 * Number:	2
 * Description: Write a program to find the taxable amount of an employee.
 * a. No tax up to $100,000 per annual income
 * b. 15% tax for $100,000 to $175,000 per annual income
 * c. 25% tax for greater than $175,000 per annual income
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <locale.h>

int main(int argc, char** argv)
{
    double amount = 0, high = 0, middle = 0, tax = 0;
    
    // get the salary from the user.
    printf("Please enter the employee's salary:\n");
    scanf("%lf", &amount);
    
    // Progressive tax
    // over $175k gets taxes a .25 e.g. if you make $200k then you will pay T = (salary - 175k) * 0.25 + $11,250 + 0;
    // $100 - $175K gets taxed at .15 e.g. if you make $150 then you will pay T = (salary - 100k) * 0.15 + 0;
    // under $100k you do not pay taxes.  I wish. :p
    if (amount > 175000)
    {
        high = (amount - 175000) * .25;
        middle = 11250; // 75000 * 0.15
    }
    else if (amount >= 100000)
    {
        middle = (amount - 100000) * .15;
    }
    
    tax = high + middle;
    
    setlocale(LC_NUMERIC, "");
    printf("The taxes on $%'.2lf is $%'.2lf\n", amount, tax);
    
    return 0;
}