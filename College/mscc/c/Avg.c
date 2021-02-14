/*
Program Name:	Avg.exe
Programmer:		Tim Beckett
Date:          11-18-02
Language:		Borland C++
Flowchart:		See Flowchart
Function:		This program will take a set of numbers and will find the average
					of 3 sets of 5 and the total average of the numbers, and it will
               also find the large value of the numbers
Inputs:        n/a
Outputs:			the table of values their averages, the total average, and the
					large value.
Other
	Programs
   	 Used:	n/a
Data
Restrictions:	n/a
Method:			find average for each set of 5 and store in an array
					find the average for all the numbers
               find the largest value of the numbers
               print the results
Printed
	Output: 		Values                         setAvg
				   -------------------------------------
					 20.50 21.30 20.00 15.20 10.30 17.46
				    21.30 20.00 15.20 10.30  9.60 15.28
			       20.00 15.20 10.30  9.60  2.30 11.48
               Large Value: 21.30
           		Total Average: 11.08
*/


# include <stdio.h>

void main()
	{
   void setAvg(double (*)[5], double *), printData(double (*)[5], double *, double, double);
   double data[3][5]={{20.5, 21.3, 20.0, 15.2, 10.3},{9.6, 2.3, 14.3, 13.1, 10.0},{1.12, 2.25,6.35, 4.6, 15.23}}, setAvgNo[3], tan, lvn, totalAvg(double (*)[5]), largeVal(double (*)[5]);

	setAvg(data, setAvgNo);
	tan = totalAvg(data);
   lvn = largeVal(data);
   printData(data, setAvgNo, tan, lvn);
   getchar();
   }

void setAvg(double (*data)[5], double *setAvgNo)
	{
   int i, j;
   double num;
	for(i=0; i<3; i++)
   	{
      num = 0.0;
      for(j=0; j<5; j++)
      	{
         num += *((*data + i)+j);
         }
      *(setAvgNo + i)= num / 5;
      }
   }

double totalAvg(double (*data)[5])
	{
   double tan, num=0.0;
   int i, j;

	for(i=0; i<3; i++)
   	{
      for(j=0; j<5; j++)
      	{
         num +=*(*(data + i)+j);
         }
      }
   tan = num/15;
   return tan;
   }

double largeVal(double (*data)[5])
	{
   double lvn;
   int i, j;
   lvn = (*data)[0];
   for(i=0; i<3; i++)
   	{
      for(j=0; j<5; j++)
      	{
         if (lvn < *((*data + i)+j))
         	lvn = *((*data + i)+j);
         }
      }
   return lvn;
   }

void printData(double (*data)[5], double *setAvgNo, double tan, double lvn)
	{
   int i, j;
   printf("Values                         setAvg\n-------------------------------------\n");
   for(i=0; i<3; i++)
   	{
      for(j=0; j<5; j++)
      	{
         printf("%6.2lf", *((*data + i)+j));
         }
      printf("%6.2lf\n", *(setAvgNo + i));
      }
   printf("Large Value:%6.2lf\nTotal Average:%6.2lf\n", lvn, tan);
   }
