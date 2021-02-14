/*
	Programer:		Timothy Beckett
	Date:			9-6-06
	Program Purpose:

	This program reads in from the user a decimal number
	in the format DDD.FFF  Then it converts it from 
	decimal to binary.
*/
# include <iostream>
# include <string>

using namespace std;

/*
This is a recursive fucntion that will calculate and print to
the screen the binary equivalent of the whole number portion
of the decimal number
*/
void print_binary(long opp);

int main()
{
	char ch = (char)0;
	string strFraction;
	long decimal = 0, fraction = 0, magnitude = 10;
	int digits;

	cout<<"Decimal number(required form d.f)?  ";
	cin>>decimal>>ch>>strFraction;

	cout<<"\n\nNumber of binary digits after the binary point?  ";
	cin>>digits;

	cout<<"\n\nThe decimal number "<<decimal<<ch<<fraction<<" is ";

	print_binary(decimal);// print the decimal part of the number in binary

	cout<<ch; //print the decimal point

	//find the magnitude of the fractional part
	for(int i = 1; i < strFraction.length() ; magnitude*=10, i++);	

	//convert string to long
	fraction = atol(strFraction.c_str());


	
	//print fractional binary digits
	/*
	The math works in the following fashion
	multiply the number by 2
	record the most signifact digit
	if product > 1 then subtract 1 from the product
	repeat process till desired number of digits is reached
	*/
	for(int i = 0; i < digits; i++)
	{
		fraction += fraction;

		if(fraction >= magnitude)
		{
			cout<<1;

			fraction -= magnitude;
		}
		else
			cout<<0;
	}

	cout<<" in binary.\n";

	return 0;
}

/*
This is a recursive fucntion that will calculate and print to
the screen the binary equivalent of the whole number portion
of the decimal number.

The logic for the math in the function:
divide the number by two
record the remander
assign opp = to the quotient
repeat the process

The procedure works in reverse
reduce the number to zero
find the remainder from smallest to greatest
so that the number will be printed in the 
correct order.
*/
void print_binary(long opp)
{
	static bool print = true;

	if(!opp) // if opp is zero print opp and quit
	{
		if (print) cout<<opp;//print leading zero for numbers < 1
		
		return;
	}
	
	print = false; //stop the printing of zero if the number is non zero

	print_binary(opp/2); //reduce the number 

	cout<<opp%2;//find the remainder

}