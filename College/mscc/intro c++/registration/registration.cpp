/*
       Program Name:	registration.exe
         Programmer:	Timothy Beckett
 	            Date: 2-22-02
 		     Language:	Borland C++
		    Flowchart:
		     Function:	to calculate the registration fee of a car based on  it's
           				weight
             Inputs: weight
				Outputs: fee
Other Programs Used: none
  Data Restrictions: weight must be in lb.
				 Method: get weight
             			is weight < 1500 yes fee = 23.75
                     is weight >= 1500 and weight<2500 fee = 27.95
                     is weight >= 2500 and weight<=3000 fee = 30.25
                     is weight > 3000	fee = 37.00
                     is fee equal to 0 then print "invalid data"
                     other wise print "Your registration fee is $" fee"."
         Looks Like: How much does the car weigh (enter weight in pounds)?
							1500
							Your registration fee is $27.95

*/
# include <iostream.h>
# include <stdio.h>

int main()
{

float weight, fee = 0;

cout<<"How much does the car weigh (enter weight in pounds)?\n";
cin>>weight;

if ((weight < 1500) && (weight > 0))
	fee = 23.75;

if ((weight >= 1500) && (weight < 2500))
	fee = 27.95;

if ((weight >= 2500) && (weight <= 3000))
	fee = 30.25;

if (weight > 3000)
	fee = 37.00;

if (fee == 0)
	cout<<"Invalid Data\n";
	else
   	cout<<"Your registration fee is $"<<fee<<endl;

 getchar();
 return 0;
}
