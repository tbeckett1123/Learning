/*
Program Name:	Date.exe
Programmer:		Tim Beckett
Date:				9-11-02
Language:		Borland C++
Flowchart:		see flowchart
Function:		This program gets the date, from the user, that they were born
					brakes the number down in to it's 4 digits and then preforms the
               indecated opperations from the user.
Inputs:			date of birth from user, int date
Outputs:			the sum of the digits, the product of the digits, or the
					users current age.
Other
	Programs
		Used:		N/A
Data
Restrictions:  N/A
Method:        Get date from user
					determine the digits
               do the operation requested by the user
					sum = num0 + num1 + num2 + num3
					product = num0 * num1 * num2 * num3
               age = 2002 - date
               display the result
Printed
	Output:     Enter the year you were born
					1950
               Make a selection:
					1) show sum of digits
					2) show product of digits
					3) show current age
					Enter your selection: 1
					The ansewer is 15
*/


# include <stdio.h>

void main()
	{
   int date, temp, num[4]={1,9}, count=0;
   printf("Enter the year you were born\n");
   scanf("%d", &date);
// is the number within range
	if (date >= 1900 && date <= 1984)
	   {
		temp = date;
      temp -= 1900;
// determin the 10's value
		while(temp >= 10)
   		{
      	temp -= 10;
			count++;
      	};

   	num[2]=count;
   	count=0;
// determin the 1's value
		while(temp >= 1)
      	{
      	temp -= 1;
			count++;
      	};

   	num[3]=count;
   	count=0;

   	printf("Make a selection: \n1) show sum of digits \n2) show product of digits\n3) show current age \nEnter your selection: ");
   	scanf("%d", &count);
// decide which opperation to do
   	switch (count)
   		{
      	case 1:	temp = num[0] + num[1] + num[2] + num[3];
      				break;
      	case 2:  temp = num[0] * num[1] * num[2] * num[3];
      				break;
      	case 3:  temp = 2002 - date;
      				break;
      	default: printf("ivalid selection");
   	   }
   	printf("The ansewer is %d", temp);
		}
   else printf("you know your not that old");
   getchar();
   getchar();
   }