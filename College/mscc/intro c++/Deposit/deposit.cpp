# include <iostream.h>
# include <stdio.h>
# include <math.h>


/* Program Name:	Deposit.exe
   Programmer:		Timothy Beckett
   Date:				2-18-02
   Language:		Borland C++
   Flowchart:
   Function:		This program will tell you how much money to deposit
   					based on how much you want to make in a given time period
                  and how much interest you will be getting
	Inputs:			Future amount = F
						Annual interest rate = R
						Years = Y
	Outputs:			Present amount = P
	Other
   	Programs
      	Used:		N/A
   Data
   Restrictions:	None
   Method:			Get F
						Get R
						Get Y
						Calculate Present amount P = F/(pow(1.0 + R, Y))
						Print "To get_"
                  		 F "_with an interest rate of_"
                         R "_over a period of_"
                         Y "_you need to deposit_" P "_today"
	Looks Like:  	Enter the amount you would like to make
   					15000.00
						Enter the Interest you will be ereaning
						8
						Enter the number of years you want it to take
						10
						To get $15000 with an interest rate of 8 % over a period
                  of 10 year(s) you need to deposit $6947.9 today


*/
int main ()
{
float F, R, P, D, Y;
cout<<"Enter the amount you would like to make\n";
cin>>F;
cout<<"Enter the Interest you will be ereaning\n";
cin>>R;
cout<<"Enter the number of years you want it to take\n";
cin>>Y;
D = R / 100;
P = F/(pow(1.0 + D, Y));
cout<<"To get $"<<F
	 <<" with an interest rate of "<<R
    <<" % over a period of "<<Y
    <<" year(s) you need  to deposit $"<<P<<" today";

    getchar();
    return 0;
}