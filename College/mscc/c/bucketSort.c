/*
Program Name:	bucketSort.exe
Programmer:		Tim Beckett
Date:				10-24-02
Language:		Borland C++
Flowchart:		See Flowchart
Function:		This program will take a list of int numbers, entered by the user,
					and will sort them least to greastest using a bucket sort method
Inputs:			numbers from the user
Outputs:       the numbers from the user sorted from least to greasest
Other
	Programs
   	 Used:	N/A
Data
Restrictions:	numbers must be decimal int's, and the user must enter
					MAX(program defined variable) number of ints.
Method:			get variables and store them in an array
               place = 1 and mod = 10
					Loop:    z++
               			take the % of  array[z] by mod and store it in x
                        calc: if x >= place(variable) calculate the
                        		place(variable) place by x-=place and term++
                              goto calc
                        put the value of array[x] into a bucketArray[9][MAX-1]
								based on the value of term if term == 0 then put
                        value[z] in bucketArray[0][a] then a++ etc. (a will be
                        b for bucketArray[1][b] etc. all varirables a - j will
                        be set to 0 every time that Loop is run)
                        if (c==0&&d==0&&e==0&&f==0&&g==0&&h==0&&i==0&&j==0)
                        then goto Loop
               now that the numbers are sorted from least to greast,
               put them back in to array and print the sorted numbers.
Printed
	Output:		Enter 10 int numbers:
					6010 80002 3001 106 507 53 4 25005 909 143
					The numbers sorted from least to greatest:
					4 53 143 106 507 909 3001 6010 25005 80002
*/
# include <stdio.h>
# define MAX 10

void main()
	{
   void bucketSort(int[]), out(int[]), in(int[]);
	int values[MAX];
   in(values);
	bucketSort(values);
	out(values);
   getchar();
   getchar();
   }

void in(int values[])
	{
// this function gets numbers from the user and put them in an array
   int x;
   printf("Enter %d int numbers:\n", MAX);
   for(x = 0; x < MAX; x++)
   	scanf("%d", &values[x]);
   }

void out(int values[])
	{
// this function prints numbers from an array
   int i;
   printf("The numbers sorted from least to greatest:\n");
   for(i = 0; i < MAX; i++)
      printf("%d ", values[i]);
   }

int a, b, c, d, e, f, g, h, i, j;

void bucketSort(int values[])
	{
/* this function sorts the values of an array from least to greast
using a bucket sort method it has two sub functions sort(...) and swap(...)*/
   void sort(int, int, int, int[][MAX-1]), swap(int[], int[][MAX-1]);
   int bucket[9][MAX-1]={{0}}, term, z, x, place = 1, mod = 10;
   do
		{
      for(z = 0; z < MAX; z++)
   		{
         x = values[z] % mod;
			for (term = 0; x >= place; x -= place, term++);
			sort(term, place, values[z], bucket);
         }
      swap(values, bucket);
      place *= 10;
	   mod *= 10;
      }
   while(!(c==0&&d==0&&e==0&&f==0&&g==0&&h==0&&i==0&&j==0));
   }

void sort(int term, int temp, int value, int bucket[][MAX-1])
	{
// this function does the sorting for bucketSort(...)
	static int check = 0;
   if (temp != check)
		{
      check = temp;
	   a = 0; b = 0; c = 0; d = 0; e = 0; f = 0; g = 0; h = 0; i = 0; j = 0;
      }
	switch (term)
     	{
      case 1:  bucket[1][b] = value; b++; break;
      case 2:	bucket[2][c] = value; c++; break;
      case 3:  bucket[3][d] = value; d++; break;
      case 4:  bucket[4][e] = value; e++;	break;
      case 5:  bucket[5][f] = value; f++; break;
      case 6:  bucket[6][g] = value; g++;	break;
      case 7:  bucket[7][h] = value; h++; break;
      case 8:  bucket[8][i] = value; i++; break;
      case 9:  bucket[9][j] = value; j++;	break;
      default:	bucket[0][a] = value; a++; break;
      }
   }

void swap(int values[], int bucket[][MAX-1])
	{
/* this function puts the sorted numbers back into the array the
bucketSort(...) it to sort */
   int z = 0 , x, move, swapVal;

	for (x = 0; x < 10; x++)
   	{
       switch (x)
       	{
			case 0:	move = a;	break;
         case 1:	move = b;	break;
         case 2:	move = c;	break;
         case 3:	move = d;	break;
         case 4:	move = e;	break;
         case 5:	move = f;	break;
         case 6:	move = g;	break;
         case 7:	move = h;	break;
         case 8:	move = i;	break;
         case 9:	move = j;	break;
         }

      for(swapVal = 0; swapVal < move; swapVal++, z++)
         values[z] = bucket[x][swapVal];
      }
   }
