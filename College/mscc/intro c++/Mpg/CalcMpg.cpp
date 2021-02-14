# include <iostream.h>
# include <stdio.h>
# include <iomanip.h>

/*
Program Name:	CalcMpg.exe
Programmer:		Tim Beckett
Date:				2-6-2002
Language:		borland C++
Function:		The purpose of this program is to calculate the gas milage of a
					tank of gas and the cumulative gas milage for a trip. It will get
               the milage at fill up, milage at next fill up, and the ammount of
               gas purchased from the user. It will display the the odometer
               reading at fill up and the odometer reading when the tank is
               empty. the ammount of gas in tank, miles driven on the tank of
               gas, and the miles per gallon for the tank. Also, it will display
               the Miles for the trip, total gas used during the trip, and the
               average miles per gallon.
Inputs:			Odometer reading at fill up (odometer1)
					Odometer reading at next fill up (odometer2)
               Gallons of gas purchased (gal)
Outputs:			Odometer1, Odometer2, gal
					miles for the tank of gas (miles)
               miles per gallon for the tank of gas (mpg)
               Gas used on trip (totalGal)
               Miles for the trip (totalMiles)
               average miles per gallon for the trip (totalMpg)
Other
	programs
   	used:		None
Data
restrictions:	-1 to end loop in varilable gal
Method:        Get gallons of gas purchased input to gal
					(enter -1 to end program)
               check gal if != -1 run loop
               Get odometer reading at fill up input to odometer1
					Get odometer reading at next fill up input to odometer2
               miles = odometer2 - odometer1
               mpg = miles / gal
               totalGal += gal
               totalMiles += miles
               totalMpg = totalMiles/ totalGal
               Print Odometer  Odometer  Fuel Miles Mpg Fuel    Miles     Mpg
               		odometer1 odometer2 gal  miles mpg totalGaltotalMilestotalMpg

Print out of program running:

How many gallons of fuel was purchased at last fill up? (Enter -1 to end)
10
What was the odometer reading at your last fill up?
100
What was the odometer reading at this fill up?
250

  Odometer  Odometer    Fuel   Miles     Mpg    Fuel   Miles    Mpg
     100.0     250.0    10.0   150.0    15.0    10.0   150.0    15.0

How many gallons of fuel was purchased at last fill up? (Enter -1 to end)
10
What was the odometer reading at your last fill up?
250
What was the odometer reading at this fill up?
500

  Odometer  Odometer    Fuel   Miles     Mpg    Fuel   Miles    Mpg
     250.0     500.0    10.0   250.0    25.0    20.0   400.0    20.0

How many gallons of fuel was purchased at last fill up? (Enter -1 to end)
-1
					
*/
int main()
{
	float gal = 0, odometer1, odometer2, miles, mpg,
			totalGal, totalMiles, totalMpg;

   cout<<"How many gallons of fuel was purchased at last fill up? (Enter -1 to end)\n";
   cin>>gal;

   while (gal != -1)
   {

   	cout<<"What was the odometer reading at your last fill up?\n";
      cin>>odometer1;
      cout<<"What was the odometer reading at this fill up?\n";
      cin>>odometer2;

      miles = odometer2 - odometer1;
      mpg = miles / gal;
      totalGal += gal;
      totalMiles += miles;
      totalMpg = totalMiles / totalGal;

      cout<<setiosflags(ios::fixed)<<setiosflags(ios::showpoint)<<setprecision(1);

      cout<<endl<<setw(10)<<"Odometer"<<setw(10)<<"Odometer"<<setw(8)<<"Fuel"
      	 <<setw(8)<<"Miles"<<setw(8)<<"Mpg"<<setw(8)<<"Fuel"<<setw(8)<<"Miles"
          <<setw(8)<<"Mpg\n"
          <<setw(10)<<odometer1<<setw(10)<<odometer2<<setw(8)<<gal
      	 <<setw(8)<<miles<<setw(8)<<mpg<<setw(8)<<totalGal<<setw(8)<<totalMiles
          <<setw(8)<<totalMpg<<endl<<endl;


      cout<<"How many gallons of fuel was purchased at last fill up? (Enter -1 to end)\n";
	   cin>>gal;
   }

return 0;
}