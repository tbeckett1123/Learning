/*
  Class Name:	Commission
  Programmer:	Tim Beckett
        Date:	2-4-03
    Language:	sun's sdk1.4.1_01 java
   Flowchart:	See Flowchart
    Function:	This program will take a user entered value(sale amount)
		and calculate the commission due.  The first $5000 will receive
		8%, the second $5000 will receive 10%, and anything over 10000 that will
		receive 12%.
      Inputs:	sale
     Outputs:	commission
Other
  Classes
        Used:	Stnd
Data
Restrictions:	At every popup box a value or string must be entered.
      Method:	get the sale amount
		Caluculate the Commision
		if	over 10000 ( (sale - 10000) * .12 ) + 900
		esleif	5000.01 to 10000 ((sale - 5000) * .10) + 400
		esle	.01 to 5000 (sale * .08)
		print the out put
Printed
      Output: 	N/A
*/


public class Commission {
	public static void main(String args[]) {
	double sale, commission = 0;
	final String control = "no";
	String again;
	do
	{	
	sale = Stnd.getD("Enter the amount of the sale:");
	if (sale > 10000.0)
		{
		commission = calc((sale - 10000.0), .12);
		commission += 900;
		}
	else if (sale > 5000.0)
		{
		commission = calc((sale - 5000.0), .10);
		commission += 400;
		}
	else if(sale > 0) commission = calc(sale, .08);
	else Stnd.out("You are either giving your product away, or you are paying someone to take it.");

	if (commission > 0) Stnd.out("The commission for $ "+sale+" is $ "+commission);

	again =	Stnd.getStr("Would you like to calculate another commission?(yes/no)");
	}
	while(!(again.equals(control))); 	
	System.exit(0);
	}
// I wrote this method to get used to writting methods in Java and passing variables to a method in Java //
	public static double calc(double amount, double rate) {
	return (amount * rate);
	}
}