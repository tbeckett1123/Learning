/*
Program Name:	convertionProgram.exe
Programmer:		Timothy Beckett
Date:				4-3-02
Language:		Borland C++
Function:		The pupose of this program is to take a user entered value
					and convert it from it's standard mearsurement to it's metric
               mearsurement
Other
	Programs
   	 Used:	N/A

Data
Restrictions:	None

For main()
	Function:	main will display a menu of choices to the user
					main will then call the appropriate function or end the program
 					based on the users input
    Inputs:		select
   Outputs:		None

For convertLenght(), convertWeight(), and convertVolume()
	Function:	the functions will display a menu of choices to the user
   				it will then assign the apprapriate value the the variable
               converter based on the users input, call the
               convertion function, and pass the value of converter to it
   Inputs:		select
   Outputs:    converter (will be passed to convertion())


For convertion()
	Function:	this function, when called will receive a floating point variable
   				called converter.  It will then get the value to be coverted from
               the user, then it will make the convertion nessary, and display
               the inUnit value and the outUnit value.
   Inputs:		inUnit, converter (will be passed by the calling function)
   Outputs:		inUnit, outUnit
*/


# include <iostream.h>
# include <stdio.h>
# include <iomanip.h>
# include <conio.h>

void convertLenght();
void convertWeight();
void convertVolume();
void convertion(float);

void main (void)
	{
   int select;
	do
   	{
      cout<<"Convert:\n"
      	 <<"1) a lenght\n"
          <<"2) a weight\n"
          <<"3) a volume\n"
          <<"4) end program\n"
          <<"Enter your selection:"; cin>>select;
      switch(select)
      	{
	      case 1: convertLenght(); break;
   	   case 2: convertWeight(); break;
	      case 3: convertVolume(); break;
   	   case 4: cout<<"Thank You for using Beckett Software\n"; break;
      	default: cout<<"Invalid Selection\n"; break;
	      }
      cout<<"press any key to conitue\n";
	   getchar();
      clrscr();
      }
   while (select != 4);
   }


void convertLenght()
	{
   int select; float converter;
   cout<<"Convert:\n"
   	 <<"1) inches to centimeters\n"
       <<"2) feet to centimeters\n"
       <<"3) feet to meters\n"
       <<"4) yards to meters\n"
       <<"5) miles to kilometers\n"
       <<"Enter your selection:"; cin>>select;
   switch (select)
   	{
      case 1: converter=2.54001; break;
      case 2: converter=30.4801; break;
      case 3: converter=.304801; break;
      case 4: converter=.914402; break;
      case 5: converter=1.60935; break;
      default: cout<<"Invalid Selection\n";
      };
   if ((select > 0) && (select < 6))
		convertion(converter);
	}


void convertWeight()
	{
   int select; float converter;
   cout<<"Convert:\n"
   	 <<"1) ounces to grams\n"
       <<"2) pounds to kiograms\n"
       <<"Enter your selection:"; cin>>select;
   switch (select)
   	{
      case 1: converter=28.349527; break;
      case 2: converter=0.453592; break;
      default: cout<<"Invalid Selection\n";
      };
   if ((select > 0) && (select < 3))
		convertion(converter);
   }


void convertVolume()
	{
   int select; float converter;
   cout<<"Convert:\n"
   	 <<"1) pints to liters\n"
       <<"2) quarters to liters\n"
       <<"3) gallons to liters\n"
       <<"Enter your selection:"; cin>>select;
   switch (select)
   	{
      case 1: converter=0.473167; break;
      case 2: converter=0.94633; break;
      case 3: converter=3.78541; break;
      default: cout<<"Invalid Selection\n";
      };
   if ((select > 0) && (select < 4))
		convertion(converter);
   }


void convertion(float converter)
	{
   float inUnit, outUnit;
	cout<<"Enter the value to be converted:"; cin>>inUnit;
   outUnit = inUnit * converter;
	cout<<setiosflags(ios::fixed)<<setiosflags(ios::showpoint)
	    <<setprecision(2);
   cout<<endl<<setw(10)<<"In Unit"<<setw(11)<<"Out Unit\n"
     	 <<setw(10)<<inUnit<<setw(10)<<outUnit<<endl;
   }
