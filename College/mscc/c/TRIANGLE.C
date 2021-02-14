/*
Program Name:	Triangle.exe
Programmer:		Tim Beckett
Date:				9-11-02
Language:		Borland c++
Flowchart:		See Flowchart
Function:		This program will get the base and a character for the face
					from the user, and then it will make the triangle.
Inputs:			base and face
Outputs:			a right triangle
Other
	Programs
   	 Used:	N\A
Data
Restrictions:	N\A
Method:			get base
					get face
               check base value change as needed
               run triangle making loop
Printed
	Output:     Enter the base of the triangle:10
					Enter the character to make the triangle from:.

					.
					. .
					. . .
					. . . .
					. . . . .
					. . . . . .
					. . . . . . .
					. . . . . . . .
					. . . . . . . . .
					. . . . . . . . . .
*/

# include <stdio.h>

void main()
	{
   int base, width, printer;
   char face;

	printf("Enter the base of the triangle:");
   scanf("%d", &base);
   getchar();

   printf("Enter the character to make the triangle from:");
   scanf("%c", &face);
// check base to see if it is in range; set it to 40 if it isn't
   if(base <=1 || base > 80)
   	base = 40;
// this loop makes the triangle
	for(width = 1; width <= base; width++)
   	{
      printf("\n");
      for(printer = 1; printer <= width; printer++)
      	printf("%c ", face);
      }

	getchar();
   getchar();
   }
