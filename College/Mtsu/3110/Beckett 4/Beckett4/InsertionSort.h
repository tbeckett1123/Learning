/*
Programmer:		Timothy Beckett
Class:			CSCI 3110
Instructor:		Dr. Seo
File:			InsertionSort.h
*********************************************
Description:	This class will hold a sorted
array, Statistical data related to the sort
algorithm run, and size of the array.  It 
encapsulates a deep copy algorithm called
Populate, and the insertion sort algorithm
called Sort.  It also will report the size of
the array called Size.  It also has overloaded
operators [], which reports back the desired
index in the array, and <<, which will print to
the screen the statistical data.
*/
# include <iostream>
# include <iomanip>
# include "Statistics.h"

using namespace std;

# ifndef INSERTIONSORT_H
# define INSERTIONSORT_H

class InsertionSort
{
//friend function

	//overloaded output operator
	//This function will display the Statical data
	//for the Insertion Sort
	//Preconditions:	Expectes an ostream and a
	//					InsertionSort
	//Postconditions:	Stats will be printed to
	//					the screen
	friend ostream& operator<<(ostream&, InsertionSort&);

public:

	//default constructor
	//Preconditions:	None
	//Postconditions:	size will be set to zero	
	//					and arr will be set to NULL
	//					Stats data will be initialized
	InsertionSort();

	//destructor
	~InsertionSort();

	//This method will make a deep copy of the provided array
	//Preconditions:	Expects an int array and its size
	//Postconditions:	size will  be set to provided size
	//					and the data from the provided
	//					array will be copied in to a mirror
	//					int array
	void Populate(const int[], const int &);

	//This method will sort the provided array using a
	//insertion sort algorithm
	//Preconditions:	The method Populate must be run first
	//Postconditions:	The array will be sorted and the following
	//					Stats will be collected and calculated:
	//					Start time, Stop time, and number of
	//					comparisons
	void Sort();

	//This method will return the size of the array stored in 
	//the InsertionSort
	//Preconditions:		None
	//Postconditions:		The size fo the array will be returned.
	int Size() const;

	//This overloaded operator will return the element referneced
	//by the provided index
	//Note:				Zero based indexing
	//Preconditions:	The Populate method should be run first
	//Postconditions:	If the index is valid the the indexed
	//					value will be returned otherwise negative
	//					one will be returned.
	int operator[](const int) const;

	//See Statistics.h for available methods and features
	//data protection for the statistics is built in to
	//the data type.
	Statistics stats;
	
private:
	int  *arr,	//pointer to int arr of size elments
		 size;	//size of the arr
	bool npop,  //only let Populate run once
		 nsort;	//only let sort run once
};

# endif
