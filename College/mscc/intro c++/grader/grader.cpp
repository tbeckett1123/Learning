/*
Program Name:		grader.exe
Programmer:			Timothy Beckett
Date:					4-26-02
Language:			Borland C++
main()
function:			Main calls 3 functions getGrades, calc, and print
						it also loops the program
inputs:				more this is a char; count is a int; grades[], *grade (is a
						pointer), and avrg are floats
outputs:          printed message "do you want to calculate more grades"
getGrades()
function:			This function gets the grades (up to 11) from the user
						if the user enters a negative number then it stops geting
                  grades
inputs:				*grade is passed to it by the function that call it
                  count is passed to it by the calling function
                  get is used to loop the function up to 11 times
outputs:				Printed message "Enter up to 11 grade. Enter a negative number
						to stop entering grades." return count to the calling function

theSum is a global variable to calc and print it is a float

calc()
function:			This function take the grades, adds them up, and finds the
						average
inputs:           *grade is passed to it by the function that call it
                  count is passed to it by the calling function
						theSum
outputs:				returns avrg to the calling function
print()
function:			This function prints theSum, avrg, and then determines if
						the grade is a A, B, C, D, or F. Then prints the grade it's
                  letter equivalent and if it is below the average it prints a
                  asteric before the grade
inputs:				*grade, count, avrg, theSum
outputs:				*grade, avrg, theSum, and the letter grade

*/

# include <iostream.h>
# include <stdio.h>
# include <conio.h>
# include <iomanip.h>

int getGrades(float*, int);
float calc(float*, int);
void print(int, float, float*);

void main()
	{
	char more;
	int count;
   float grades[10], *grade, avrg;
	grade = &grades[0];
	cout<<setiosflags(ios::fixed)<<setiosflags(ios::showpoint)
   	 <<setprecision(2);
	do
   	{
      count = 0;
   	count = getGrades(grade, count);
   	avrg = calc(grade, count);
		print(count, avrg, grade);
		cout<<"would you like to calculate more grades(y/n)?";cin>>more;
	   clrscr();
      }
   while (more == 'y');
   }

int getGrades(float *grade, int count)
	{
   cout<<"Enter up to 11 grades\n"<<"Enter a negative number to stop\n";
   for (int get = 0; get <= 11; get++)
   	{
		cin>>*grade;

      if (*grade<0)
      	get = 11;
		else
      	{
         *grade++;
         count++;
         }
      }
	clrscr();
   return count;
   }
float theSum;
float calc(float  *grade, int count)
	{
   float avrg;
   theSum = 0;
   for (int sum = 0; sum<count; sum++)
   	{
		theSum += *grade;
      *grade++;
      }
	avrg = theSum / count;
   return avrg;
   }

void print(int count, float avrg, float *grade)
	{
   char letter;
	cout<<"The sum of the grades is "<<theSum<<endl
   	 <<"The average of the grades is "<<avrg<<endl
       <<"The grades with an * beside them are below the Average\n"
       <<"Here are the grades\n";
   for (int print = 0; print < count; print++)
   	{
      if (*grade >= 90.0)
        	letter = 'A';
      else if (*grade >= 80.0)
        	letter = 'B';
   	else if (*grade >= 70.0)
        	letter = 'C';
   	else if (*grade >= 60.0)
        	letter = 'D';
  		else
        letter ='F';

      if (*grade < avrg)
	      cout<<"* "<<*grade<<" is a "<<letter<<endl;
   	else
        	cout<<"  "<<*grade<<" is a "<<letter<<endl;
      *grade++;
      }
   }
