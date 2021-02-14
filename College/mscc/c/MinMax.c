/*
Program Name:  MinMax.exe
Programmer:		Tim Beckett
Date:          Septmeber 30, 2002
Language:		Borland C++
Flowchart:		See Flowchart
Function:		This program reads in a list of numbers and prints out the min,
					max, and average.
Inputs:			a list of numbers
Outputs:			min, max, average
Other
	Programs
   	 Used:	NA
Data
Restrictions:	NA
Method:			Users enters a a list of numbers and ends with -0.99
					loop: get number until number equals -0.99
               min = number if number < min
               max = mumber if number > max
               sum the numbers
               count the numbers
               goto loop
               average = sum / count
               print the min max and average

Printed
	Output:		enter a list of floating point numbers (enter -0.99 to stop list):
					90 45 80 48 45 -0.99
					Min = 45.00
					Max = 90.00
					Average = 61.60
*/
# include <stdio.h>

int main()
	{
	float findMin(float, float);
   float findMax(float, float);
   void printMinMaxArvg(float, float, float);
	float minVal, maxVal, x, y = 0.0, count, avrg;
   printf("enter a list of floating point numbers (enter -0.99 to stop list):\n");
	scanf("%f", &x);
   minVal = x;
   maxVal = x;
   for(; x > -0.99; count++)
		{
   	minVal = findMin(x, minVal);
  		maxVal = findMax(x, maxVal);
		y+=x;
		scanf("%f", &x);
		}
   avrg = y / count;
	printMinMaxArvg(minVal, maxVal, avrg);
      getchar();
   	getchar();
   return 0;
   }

float findMin(float compMin, float tempMin)
	{
   if (compMin < tempMin)
   	tempMin = compMin;
   return tempMin;
   }

float findMax(float compMax, float tempMax)
	{
   if (compMax > tempMax)
   	tempMax = compMax;
   return tempMax;
   }

void printMinMaxArvg(float printMin, float printMax, float printAvrg)
	{
   printf("Min = %.2f\nMax = %.2f\nAverage = %.2f\n", printMin, printMax, printAvrg);
   }
