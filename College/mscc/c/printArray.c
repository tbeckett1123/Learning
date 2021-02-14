/*
Program Name:  printArray.exe
Programmer:		Tim Beckett
Date:				October, 7,2002
Language:		Borland C++
Flowchart:		See Flowchart
Function:		this program will take a predefined array, print the array,
					reverse the array, and then print the array again
Inputs:        NA
Outputs:       array
Other
	Programs
   	 Used:	NA
Data
Restrictions:	NA
Method:			declare array and set array values
					printarray
               	print temparray[*]
                  loop till end of temparray
               reverse the array
               	reverse temparray[min], temparray[max]
               	min++, max--
                  loop till all variables are swapped
               printarray again
Printed
	Output:		Array[0] = 10
					Array[1] = 20
					Array[2] = 30
					Array[3] = 40
					Array[4] = 50
					Array[5] = 60
					Array[6] = 70
					Array[7] = 80
					Array[8] = 90
					Array[9] = 100
					Array[10] = 110
					Array[11] = 120
					Array[12] = 130
					Array[13] = 140
					Array[14] = 150
					Array[0] = 150
					Array[1] = 140
					Array[2] = 130
					Array[3] = 120
					Array[4] = 110
					Array[5] = 100
					Array[6] = 90
					Array[7] = 80
					Array[8] = 70
					Array[9] = 60
					Array[10] = 50
					Array[11] = 40
					Array[12] = 30
					Array[13] = 20
					Array[14] = 10
*/

# include <stdio.h>

void main()
	{
   void printArray(int[]), reverse(int[]);
   int array[15]={10,20,30,40,50,60,70,80,90,100,110,120,130,140,150};
   printArray(array);
   reverse(array);
   printArray(array);
	getchar();
   getchar();
   }

void reverse(int tempArray[])
	{
   int swap, min, max;
	for(min = 0, max = 14; min <= max; min++, max--)
   	{
      swap = tempArray[min];
      tempArray[min] = tempArray[max];
      tempArray[max] = swap;
      }
   }

void printArray(int tempArray[])
	{
   int print;
   for(print=0; print < 15; print++)
   	printf("Array[%d] = %d\n", print, tempArray[print]);
   }
