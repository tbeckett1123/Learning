/*
Program Name:  Pie.exe
Programmer:		Tim Beckett
Date:				September 23, 2002
Language:		Borland C++
Flowchart:		See Flowchart
Function:		This program calculates pie and counts the number of calcluations
					it took.  Then it put the ansewer on the screen
Inputs:			N/A
Outputs:			pie and term
Other
	Programs
   	 Used:	N/A
Data
Restrictions:	N/A
Method:			loop
		         check to see if it is time to stop
					if term == check
               {pi -= (4.0 / x)
               check+=2}
               if term == check1
               {pi += (4.0 / x)
               check1+=2}
               if pi >= 3.14159
               {print pi and term
               if pi > 3.14159 && pi < 3.141599
               it is time to stop}
               term++
               end loop
Printed
	Output:     // last five lines of printed output //
   				Pi = 3.141602   Term = 166103
					Pi = 3.141602   Term = 166105
					Pi = 3.141602   Term = 166107
					Pi = 3.141602   Term = 166109
					Pi = 3.141590   Term = 166110

*/
# include <stdio.h>
void main()
	{
   int check = 0, check1 = 1, term = 0, checkStop = 1, stop = 0;
   float pi = 4.0, x = 3.0, y = 3.14;
// when pi == 3.141590, stop = 1
   for(; checkStop != stop; term++)
   	{
// if term is even
      for(; term == check; check += 2)
      	pi -= (4.0 / x);
// if term is odd
      for(; term == check1; check1 +=2)
	      pi += (4.0 / x);
// do regardless of term value
      x += 2.0;
// print the output only when pi > 3.14159
		if (pi >= 3.14159)
      	{
   	 		printf("Pi = %f   Term = %d \n", pi, term);
// set stop = 1 when it is time
   			if(pi > 3.14159 && pi < 3.141599)
   				stop = 1;
   			else
   				stop = 0;
      	}
      }
	getchar();
   }