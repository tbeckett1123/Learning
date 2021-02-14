/*
Programmer:		Timothy Beckett
Class:			CSCI 3110
Instructor:		Dr. Seo
File:			Client.cpp
*********************************************
Description: 
	The purpose of this program is to analize 
the following sorting alogrithms: heap sort, 
insertion sort, merge sort, and quick sort.
Each algorithm will be tested on four array
sizes: 10, 50, 100, 500.  Each array size will
be tested with the following starting indexes:
1, 101, 201, 301, 401.  Each sorting algorithm
will be  test once on a sorted array and once
on a reversed array. It will produce the 
following output (output.txt):the best, worst, 
and average case number of comparisons on the 
array size.  
*/

# include "HeapSort.h"
# include "InsertionSort.h"
# include "MergeSort.h"
# include "QuickSort.h"
# include <iomanip>
# include <iostream>
# include <string>
# include <fstream>

using namespace std;

const int MAX_SIZE = 1000;

struct Array
{
	int a[MAX_SIZE],	//the array define with MAX_SIZE elements
		size;			//the actual number of elements used
};

// ************* prototypes *************
void read(Array &, char *);
void write(int [4][4][3]);

void copy(Array*, Array&, int, int);
void copy(Array*, HeapSort&);

void init(Array *[][5], int);
void setupArrays(Array *[][5], Array&);
void cleanUp(Array *[][5], int);

/*
all 4 of the setUp4Sort functions contain the same code
I had to use different function because each sort object
is a different data type.
*/

void setUp4Sort(HeapSort [][5], Array *[][5], Array&);
void setUp4Sort(InsertionSort [][5], Array *[][5], Array&);
void setUp4Sort(MergeSort [][5], Array *[][5], Array&);
void setUp4Sort(QuickSort [][5], Array *[][5], Array&);

/*
all 4 of the sort functions contain the same code
I had to use different function because each sort object
is a different data type.
*/

void sort(HeapSort [][5]);
void sort(InsertionSort [][5]);
void sort(MergeSort [][5]);
void sort(QuickSort [][5]);

/*
all 4 of the average functions contain the same code
I had to use different function because each sort object
is a different data type.
*/


int average(HeapSort [][5], int);
int average(InsertionSort [][5], int);
int average(MergeSort [][5], int);
int average(QuickSort [][5], int);

/*
all 4 of the best functions contain the same code
I had to use different function because each sort object
is a different data type.
*/

int best(HeapSort [][5], int);
int best(InsertionSort [][5], int);
int best(MergeSort [][5], int);
int best(QuickSort [][5], int);

/*
all 4 of the worst functions contain the same code
I had to use different function because each sort object
is a different data type.
*/

int worst(HeapSort [][5], int);
int worst(InsertionSort [][5], int);
int worst(MergeSort [][5], int);
int worst(QuickSort [][5], int);

void calculate(int [4][4][3], HeapSort [][5], InsertionSort [][5], MergeSort [][5], QuickSort [][5]);
// *********** end prototypes ***********

int main()
{
	//the arrays (hs[5][5], is[5][5], ms[5][5], qs[5][5]) will be stored in this fashion:
	
	//row 0 ( 10 random ),		column 0 starting with index 0
	//							column 1 starting will index 100
	//							column 2 starting with index 200
	//							column 3 starting with index 300
	//							column 4 starting with index 400
	
	//row 1 ( 50 random ),		column 0 starting with index 0
	//							column 1 starting will index 100
	//							column 2 starting with index 200
	//							column 3 starting with index 300
	//							column 4 starting with index 400
	
	//row 2 ( 100 random ),		column 0 starting with index 0
	//							column 1 starting will index 100
	//							column 2 starting with index 200
	//							column 3 starting with index 300
	//							column 4 starting with index 400

	//row 3 ( 500 random ),		column 0 starting with index 0
	//							column 1 starting will index 100
	//							column 2 starting with index 200
	//							column 3 starting with index 300
	//							column 4 starting with index 400

	//row 4 ( full array),		column 0 sorted
	//							column 1 reverse
	//							columns 2,3,4 not used
	
	HeapSort		hs[5][5];
	InsertionSort	is[5][5];
	MergeSort		ms[5][5];
	QuickSort		qs[5][5];

	int results[4][4][3]; //results will be 
	//0 heap		|	0 10	|	0 best, 1 worst, 2 average
	//1	Insertion	|	1 50	|	0 best, 1 worst, 2 average
	//2 merge		|	2 100	|	0 best, 1 worst, 2 average
	//3 quick		|	3 500	|	0 best, 1 worst, 2 average
	
	Array randArr, revArr, *arr[5][5];
	//the array arr will be setup in this fashion:
	
	//row 0 ( 10 random )		column 0 starting with index 0
	//							column 1 starting will index 100
	//							column 2 starting with index 200
	//							column 3 starting with index 300
	//							column 4 starting with index 400
	
	//row 1 ( 50 random )		column 0 starting with index 0
	//							column 1 starting will index 100
	//							column 2 starting with index 200
	//							column 3 starting with index 300
	//							column 4 starting with index 400

	//row 2 ( 100 random )		column 0 starting with index 0
	//							column 1 starting will index 100
	//							column 2 starting with index 200
	//							column 3 starting with index 300
	//							column 4 starting with index 400

	//row 3 ( 500 random )		column 0 starting with index 0
	//							column 1 starting will index 100
	//							column 2 starting with index 200
	//							column 3 starting with index 300
	//							column 4 starting with index 400

	// row 4 full array			column 0 sorted
	//							column 1 reverse
	//							columns 2-4 not used (will have Array 
	//												 structures	in them)
	

	read(randArr, "random.txt");  //read in the unsorted arrays of ints
	read(revArr, "reverse.txt");

	init(arr, 5);	//setup arr with Arrays

	setupArrays(arr, randArr);	//copy sub arrays to be sorted

	setUp4Sort(hs, arr, revArr); //Placing Arrays in sorting object
	setUp4Sort(is, arr, revArr);
	setUp4Sort(ms, arr, revArr);
	setUp4Sort(qs, arr, revArr);
		
	sort(hs); //run all sorting algorithms for all sizes, reverse, and sorted
	sort(is);
	sort(ms);
	sort(qs);

	calculate(results, hs, is, ms, qs);
		
	write(results);

	cleanUp(arr, 5);	//clean up dynamic memory used

	return 0;
}

void read(Array & a, char * file)
/*
This function will read the desired number of
ints from the file.
Preconditions:	provide the Array a of max_size
Postconditions:	the arr will be initialized
				and the number of elements used
				will be counted and stored in size
*/
{
	ifstream fin;

	fin.open(file);

	a.size = 0;

	if(!fin)
		return;

	for(; a.size < MAX_SIZE && !fin.eof(); a.size++)
		fin>>a.a[a.size];

	fin.close();
}

void setupArrays(Array *arr[][5], Array& randArr)
/*
This function will copy each sub array starting from
the desired index to the desired size

Preconditions:	init and read fucntions must have already be run
				Provide the Array to copy to ( Array[][5] )
				Provide the Array to copy from ( Array & )
Postconditions:	The provided 2-d array will be setup with data
				for the desired data sets for sorts
				see comment on Array *arr[5][5] in the main program
				for data oraginization.
*/
{
	HeapSort sortedHs;

	for(int i = 0, j = 0; i < 5; i++, j+= 100)
		copy(arr[0][i], randArr,   j, 10);	//setting up arrays of size ten
	
	for(int i = 0, j = 0; i < 5; i++, j+= 100)
		copy(arr[1][i], randArr,   j, 50); //setting up arrays of size fifty
	
	for(int i = 0, j = 0; i < 5; i++, j+= 100)
		copy(arr[2][i], randArr,   j, 100); //setting up arrays of size one hundred
	
	for(int i = 0, j = 0; i < 5; i++, j+= 100)
		copy(arr[3][i], randArr,   j, 500); //setting up arrays of size five hundred

	sortedHs.Populate(randArr.a, randArr.size);	//setting up sorted array
	sortedHs.Sort();
	copy(arr[4][0], sortedHs);
}

void copy(Array* c, Array & o, int startPoint, int size)
/*
This fucntion will copy the desired number of int from
the original Array into c.  Put another way this will copy
a sub array of the orginal array

Precondtions:	Provide the Array to copy to(Array * already intialized)
				Provide the Array to copy from (Array&)
				Provide the starting index in the original Array (int)
				Provide the number of elements to copy (int)
Postcondtions:	The desired elements will be copied from the original
				Array to the copy pointer and the size of the copy
				will be intialized to the size desired
*/
{
	for(int i = startPoint ; (i-startPoint) < size ; i++)
		c->a[i-startPoint] = o.a[i];

	c->size = size;
}

void copy(Array* c, HeapSort& o)
/*
This funcition will copy an array from a HeapSort object into an Array
Preconditions:	Provide the Array to copy to (Array * already intialized)
				Provide the HeapSort to copy from (HeapSort&)
Postconditions:	The Array will be copied from the HeapSort to the Array
				and the HeapSort size will be stored in the Array size
*/
{
	c->size = o.Size();

	for(int i = 0; i < c->size; i++)
		c->a[i] = o[i];
}

void init(Array *arr[][5], int size)
/*
This function will initialize a 2-d array of Array pointers
Proconditions:	Provide 2-d array ( Array *[x][5] )
				Provide the number of rows(x) ( int )
Postcondtions:	the 2-d array will be initialized
Note:			Associated function cleanUp
*/
{
	for(int i = 0; i < size; i++)
		for(int j = 0; j < 5; j++)
			arr[i][j] = new Array();
}

void cleanUp(Array *arr[][5], int size)
/*
This function will delete all memory allocated in the provided array.
It assumes that all rows and columns from 0,0 to size, 4 will be
initialized.
Preconditions:	Provide 2-D array ( Array * [][5] )
				Provide the number of rows (int)
Postconditions:	all memory in the array will be deleted
*/
{
	for(int i = 0; i < size; i++)
		for(int j = 0; j < 5; j++)
			delete arr[i][j];
}

void setUp4Sort(HeapSort hs[][5], Array *arr[][5], Array & reverse)
/*
This fucntion sets up the HeapSort array with its data to be sorted
Preconditions:	Provide HeapSort array [][5]
				Provide Array [][5] (ADT)
					must have run init and setUpArrays functions
				Provide Array & (ADT)
Postconditions:	HeapSort [][5] will be set up with data as noted
				declaration of the sort [][5] at the top of the
				main function.
*/
{
	hs[4][0].Populate(arr[4][0]->a, arr[4][0]->size); //setting up sorted
	hs[4][1].Populate(reverse.a, reverse.size);		  //setting up reversed

	for(int i = 0; i < 4; i++)				//setting up all other arrays
		for(int j = 0; j < 5; j++)
			hs[i][j].Populate(arr[i][j]->a, arr[i][j]->size);
		
}

void setUp4Sort(InsertionSort is[][5], Array *arr[][5], Array & reverse)
/*
This fucntion sets up the InsertionSort array with its data to be sorted
Preconditions:	Provide InsertionSort array [][5]
				Provide Array [][5] (ADT)
					must have run init and setUpArrays functions
				Provide Array & (ADT)
Postconditions:	InsertionSort [][5] will be set up with data as noted
				declaration of the sort [][5] at the top of the
				main function.
*/
{
	is[4][0].Populate(arr[4][0]->a, arr[4][0]->size); //setting up sorted
	is[4][1].Populate(reverse.a, reverse.size);		  //setting up reversed

	for(int i = 0; i < 4; i++)				//setting up all other arrays
		for(int j = 0; j < 5; j++)
			is[i][j].Populate(arr[i][j]->a, arr[i][j]->size);
}

void setUp4Sort(MergeSort ms[][5], Array *arr[][5], Array & reverse)
/*
This fucntion sets up the MergeSort array with its data to be sorted
Preconditions:	Provide HeapSort array [][5]
				Provide Array [][5] (ADT)
					must have run init and setUpArrays functions
				Provide Array & (ADT)
Postconditions:	MergeSort [][5] will be set up with data as noted
				declaration of the sort [][5] at the top of the
				main function.
*/
{
	ms[4][0].Populate(arr[4][0]->a, arr[4][0]->size); //setting up sorted
	ms[4][1].Populate(reverse.a, reverse.size);		  //setting up reversed

	for(int i = 0; i < 4; i++)				//setting up all other arrays
		for(int j = 0; j < 5; j++)
			ms[i][j].Populate(arr[i][j]->a, arr[i][j]->size);
}

void setUp4Sort(QuickSort qs[][5], Array *arr[][5], Array & reverse)
/*
This fucntion sets up the QuickSort array with its data to be sorted
Preconditions:	Provide QuickSort array [][5]
				Provide Array [][5] (ADT)
					must have run init and setUpArrays functions
				Provide Array & (ADT)
Postconditions:	QuickSort [][5] will be set up with data as noted
				declaration of the sort [][5] at the top of the
				main function.
*/
{
	qs[4][0].Populate(arr[4][0]->a, arr[4][0]->size); //setting up sorted
	qs[4][1].Populate(reverse.a, reverse.size);		  //setting up reversed

	for(int i = 0; i < 4; i++)				//setting up all other arrays
		for(int j = 0; j < 5; j++)
			qs[i][j].Populate(arr[i][j]->a, arr[i][j]->size);
}

void sort(HeapSort hs[][5])
/*
Sorts the data

Preconditions:	Provide HeapSort[][5]
Posconditions:	data will be sorted
*/
{
	hs[4][0].Sort();
	hs[4][1].Sort();

	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 5; j++)
			hs[i][j].Sort();
}

void sort(InsertionSort is[][5])
/*
Sorts the data

Preconditions:	Provide InsertionSort[][5]
Posconditions:	data will be sorted
*/
{
	is[4][0].Sort();
	is[4][1].Sort();

	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 5; j++)
			is[i][j].Sort();
}

void sort(MergeSort ms[][5])
/*
Sorts the data

Preconditions:	Provide MergeSort[][5]
Posconditions:	data will be sorted
*/
{
	ms[4][0].Sort();
	ms[4][1].Sort();

	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 5; j++)
			ms[i][j].Sort();
}

void sort(QuickSort qs[][5])
/*
Sorts the data

Preconditions:	Provide QuickSort[][5]
Posconditions:	data will be sorted
*/
{
	qs[4][0].Sort();
	qs[4][1].Sort();

	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 5; j++)
			qs[i][j].Sort();
}

void write(int results[4][4][3])
/*
Write the results of each sort to the screen and file ("output.txt")
				:data layout:
Algorythm      ArraySize   Best      Worst     Average
------------------------------------------------------
HeapSort       10          ?         ?         ?
               50          ?         ?         ?
               100         ?         ?         ?
               500         ?         ?         ?
InsertionSort  10          ?         ?         ?
               50          ?         ?         ?
               100         ?         ?         ?
               500         ?         ?         ?
MergeSort      10          ?         ?         ?
               50          ?         ?         ?
               100         ?         ?         ?
               500         ?         ?         ?
QuickSort      10          ?         ?         ?
               50          ?         ?         ?
               100         ?         ?         ?
               500         ?         ?         ?
				:end data layout:

Preconditions:	Provide int[4][4][3]
					Must run calculate first
Postconditons:	Data will be printed to the screen and to the file
				output.txt
*/
{
	ofstream fout;

	string sortName[4][4] = { "HeapSort",      " ", " ", " ",
							  "InsertionSort", " ", " ", " ",
							  "MergeSort",     " ", " ", " ",
							  "QuickSort",     " ", " ", " "  };

	int size [] = { 10, 50, 100, 500 };

	fout.open("output.txt");

	cout<<left<<setw(15)<<"Algorythm"<<setw(12)<<"ArraySize"<<setw(10)<<"Best"<<setw(10)<<"Worst"<<setw(10)<<"Average"<<endl
		<<setfill('-')<<setw(54)<<"-"<<setfill(' ')<<endl;

	fout<<left<<setw(15)<<"Algorythm"<<setw(12)<<"ArraySize"<<setw(10)<<"Best"<<setw(10)<<"Worst"<<setw(10)<<"Average"<<endl;

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			cout<<left<<setw(15)<<sortName[i][j]<<setw(12)<<size[j];

			fout<<left<<setw(15)<<sortName[i][j]<<setw(12)<<size[j];

			for(int k = 0; k < 3; k++)
			{
				cout<<left<<setw(10)<<results[i][j][k];

				fout<<left<<setw(10)<<results[i][j][k];
			}
			cout<<endl;
			fout<<endl;
		}
	}

	fout.close();
}

int average(HeapSort hs[][5], int i)
/*
This fucntion will average the number of comparisions 
in the row of the provide index
Precondtions:	Provide HeapSort[][5]
				Provide (index) int
Postcontions:	The aveverage will be returned
*/
{
	int comp = 0;
	int t = 2;
	comp += hs[i][0].stats.counter.Return();
	comp += hs[i][1].stats.counter.Return();
	if(i < 4)
	{
		comp += hs[i][2].stats.counter.Return();
		comp += hs[i][3].stats.counter.Return();
		comp += hs[i][4].stats.counter.Return();
		t = 5;
	}

	return comp/t;
}

int average(InsertionSort is[][5], int i)
/*
This fucntion will average the number of comparisions 
in the row of the provide index
Precondtions:	Provide InsertionSort[][5]
				Provide (index) int
Postcontions:	The aveverage will be returned
*/
{
	int comp = 0;
	int t = 2;
	comp += is[i][0].stats.counter.Return();
	comp += is[i][1].stats.counter.Return();
	if(i < 4)
	{
		comp += is[i][2].stats.counter.Return();
		comp += is[i][3].stats.counter.Return();
		comp += is[i][4].stats.counter.Return();
		t = 5;
	}

	return comp/t;
}

int average(MergeSort ms[][5], int i)
/*
This fucntion will average the number of comparisions 
in the row of the provide index
Precondtions:	Provide MergeSort[][5]
				Provide (index) int
Postcontions:	The aveverage will be returned
*/
{
	int comp = 0;
	int t = 2;
	comp += ms[i][0].stats.counter.Return();
	comp += ms[i][1].stats.counter.Return();
	if(i < 4)
	{
		comp += ms[i][2].stats.counter.Return();
		comp += ms[i][3].stats.counter.Return();
		comp += ms[i][4].stats.counter.Return();
		t = 5;
	}

	return comp/t;
}

int average(QuickSort qs[][5], int i)
/*
This fucntion will average the number of comparisions 
in the row of the provide index
Precondtions:	Provide QuickSort[][5]
				Provide (index) int
Postcontions:	The aveverage will be returned
*/
{
	int comp = 0;
	int t = 2;
	comp += qs[i][0].stats.counter.Return();
	comp += qs[i][1].stats.counter.Return();
	if(i < 4)
	{
		comp += qs[i][2].stats.counter.Return();
		comp += qs[i][3].stats.counter.Return();
		comp += qs[i][4].stats.counter.Return();
		t = 5;
	}

	return comp/t;
}


int best(HeapSort hs[][5], int i)
/*
this fucntion will return the count of the sort with 
the lowest number of comparisions
Precondtions:	Provide HeapSort[][5]
				Provide (index) int
Postconditions:	The lowest count is returned
*/
{
	int low = hs[i][0].stats.counter.Return();

	for(int j = 1; j < 5; j++)
	{
		if(low > hs[i][j].stats.counter.Return())
			low = hs[i][j].stats.counter.Return();
	}

	return low;
}
int best(InsertionSort is[][5], int i)
/*
this fucntion will return the count of the sort with 
the lowest number of comparisions
Precondtions:	Provide InsertionSort[][5]
				Provide (index) int
Postconditions:	The lowest count is returned
*/
{
	int low = is[i][0].stats.counter.Return();

	for(int j = 1; j < 5; j++)
	{
		if(low > is[i][j].stats.counter.Return())
			low = is[i][j].stats.counter.Return();
	}

	return low;
}
int best(MergeSort ms[][5], int i)
/*
this fucntion will return the count of the sort with 
the lowest number of comparisions
Precondtions:	Provide MergeSort[][5]
				Provide (index) int
Postconditions:	The lowest count is returned
*/
{
	int low = ms[i][0].stats.counter.Return();

	for(int j = 1; j < 5; j++)
	{
		if(low > ms[i][j].stats.counter.Return())
			low = ms[i][j].stats.counter.Return();
	}

	return low;
}

int best(QuickSort qs[][5], int i)
/*
this fucntion will return the count of the sort with 
the lowest number of comparisions
Precondtions:	Provide QuickSort[][5]
				Provide (index) int
Postconditions:	The lowest count is returned
*/
{
	int low = qs[i][0].stats.counter.Return();

	for(int j = 1; j < 5; j++)
	{
		if(low > qs[i][j].stats.counter.Return())
			low = qs[i][j].stats.counter.Return();
	}

	return low;
}

int worst(HeapSort hs[][5], int i)
/*
This function will return the count of the sort with
highest number of comparsions
Precondtions:	Provide HeapSort[][5]
				Provide (index) int
Postconditions:	The highest count is returned
*/
{
	int high = hs[i][0].stats.counter.Return();

	for(int j = 1; j < 5; j++)
	{
		if(high < hs[i][j].stats.counter.Return())
			high = hs[i][j].stats.counter.Return();
	}

	return high;
}

int worst(InsertionSort is[][5], int i)
/*
This function will return the count of the sort with
highest number of comparsions
Precondtions:	Provide InsertionSort[][5]
				Provide (index) int
Postconditions:	The highest count is returned
*/
{
	int high = is[i][0].stats.counter.Return();

	for(int j = 1; j < 5; j++)
	{
		if(high < is[i][j].stats.counter.Return())
			high = is[i][j].stats.counter.Return();
	}

	return high;
}

int worst(MergeSort ms[][5], int i)
/*
This function will return the count of the sort with
highest number of comparsions
Precondtions:	Provide MergeSort[][5]
				Provide (index) int
Postconditions:	The highest count is returned
*/
{
	int high = ms[i][0].stats.counter.Return();

	for(int j = 1; j < 5; j++)
	{
		if(high < ms[i][j].stats.counter.Return())
			high = ms[i][j].stats.counter.Return();
	}

	return high;
}

int worst(QuickSort qs[][5], int i)
/*
This function will return the count of the sort with
highest number of comparsions
Precondtions:	Provide QuickSort[][5]
				Provide (index) int
Postconditions:	The highest count is returned
*/
{
	int high = qs[i][0].stats.counter.Return();

	for(int j = 1; j < 5; j++)
	{
		if(high < qs[i][j].stats.counter.Return())
			high = qs[i][j].stats.counter.Return();
	}

	return high;
}


void calculate(int results[4][4][3], HeapSort hs[][5], InsertionSort is[][5], MergeSort ms[][5], QuickSort qs[][5])
/*
This function colects the stats from each Sort array object and stores it in
resulsts
Precondtions:	Provide int [4][4][3]
				Provide HeapSort[][5]
				Provide	InsertionSort[][5]
				Provide MergeSort[][5]
				Provide QuickSort[][5]
Postcondtions:	The stats will be stored in the int [4][4][3]
					see the declaration of int results[4][4][3]
					in main	for data layout details
*/
{
	for(int i = 0; i < 4; i++)
	{
		results[0][i][0] = best(hs, i);
		results[0][i][1] = worst(hs, i);
		results[0][i][2] = average(hs, i);
	}

	for(int i = 0; i < 4; i++)
	{
		results[1][i][0] = best(is, i);
		results[1][i][1] = worst(is, i);
		results[1][i][2] = average(is, i);
	}
	
	for(int i = 0; i < 4; i++)
	{
		results[2][i][0] = best(ms, i);
		results[2][i][1] = worst(ms, i);
		results[2][i][2] = average(ms, i);
	}

	for(int i = 0; i < 4; i++)
	{
		results[3][i][0] = best(qs, i);
		results[3][i][1] = worst(qs, i);
		results[3][i][2] = average(qs, i);
	}
}
