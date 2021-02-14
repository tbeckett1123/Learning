# include <iostream.h>
# include <iomanip.h>
# include <stdio.h>
# include <math.h>

/*	Program Name:	Interest.exe
	Programmer:		Timothy Beckett
   Date:				2-15-02
   Lanuage:			Borland C++
   Flowchart:
   Function:		This program calculates the effective interest rate for a
   					stated interest rate and it's compound period in a physical
                  year.
   Inputs:			Stated Interest Rate "R"
   					Compounded period "M"
   Output:			Effective Interest Rate: "S"
   					Stated Interest Rate "R"
                  Compound period "M"

						Looks Like:

Enter Interest Rate(as a percent)
6 (<-- input from user)
Enter how many times is it compounded
4 (<-- input from user)
The Effective Annual Rate is   6.136 %
When stated rate is     6 %
and it is compounded    4 times a year

   Other
   	Programs
      	Used:		N/A
   Data
   Restrictions:  Stated rate must be entered as a percent.
   					Compound period must be a hole positive number.
   Method:			Get stated rate "R" from user
   					Get compound period "M" from user
                  Convert R to a decimal I = R/100
                  Calculate Effetive interest rate E = pow((1 + I / M),M)-1
                  Convert E to a decimal S = E * 100
                  Print: S, R, M
                  */
int main()
{

float E,I,R,S;
int M;

cout<<"Enter Interest Rate(as a percent)\n";
cin>>R;

cout<<"Enter how many times is it compounded\n";
cin>>M;

I = R / 100;
E = pow((1 + I / M),M)-1;
S = E * 100;

cout	<<"The Effective Annual Rate is "
      <<setw(7)<<setprecision(4)<<S
      <<" %"<<endl
      <<"When stated rate is "
      <<setw(5)<<setprecision(4)<<R
      <<" %"<<endl
      <<"and it is compounded "<<setw(4)<<M<<" times a year";

getchar();
return 0;

}
