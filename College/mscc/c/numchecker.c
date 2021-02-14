
/*
Program Name:	numchecker.exe
Programmer:		Tim Beckett
Date:				9-11-02
Language:		borland c++
Flowchart:		See Flowchart
Function:		This program will get a integer value and then determine if the
					number is divisable by 2, 3, 5, 7.
Inputs:			a integer from the user iVal
Outputs:			wheather or not the integer is divisable by 2, 3, 5, 7.
Other
	Programs
   	 Used:	N\A
Data
Restrictions:	N\A
Method:        get a number
					is the number in range
               qval = ival / mult[]
               does ival == qval * mult[]
               display the results
Printed
	Output:     enter a integer
					25




					25 is not evenly divisable by 2
					25 is not evenly divisable by 3
					25 is evenly divisable by 5
					25 is not evenly divisable by 7
*/

# include <stdio.h>


void main()
	{
   int iVal, qVal, rVal, count, mult[4]={2,3,5,7};

   printf("enter a integer\n");
   scanf("%d", &iVal);
// is the number in range
	if (iVal < 10 || iVal > 100)
   	printf("the number is out of range");
   else {
      printf("\n\n\n\n");
// checks to see if the number is divisable by the prime numbers and prints
// the results
   	for (count = 0; count <=3; count++)
   		{
	   	qVal = iVal / mult[count];

		   if (qVal* mult[count] == iVal)
   			rVal = mult[count];
   		else
	   		rVal = 0;

	      if (rVal != 0)
         	printf("%d is evenly divisable by %d\n", iVal, mult[count]);
         else
         	printf("%d is not evenly divisable by %d\n", iVal, mult[count]);
      	};
   }

	getchar();
   getchar();
   }


