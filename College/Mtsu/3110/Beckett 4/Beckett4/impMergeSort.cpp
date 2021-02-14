/*
Programmer:		Timothy Beckett
Class:			CSCI 3110
Instructor:		Dr. Seo
File:			impMergeSort.cpp
*/

# include "MergeSort.h"

/********************** Friend Function ***************************/
ostream& operator<<(ostream& out, MergeSort& data)
{
	out <<setw(11)<<"Merge Sort"
		<<setw(5)<<data.size
		<<setw(5)<<data.stats.counter
		<<data.stats.time_tracker.TimeLapse()
		<<endl;

	return out;
}

/*********************** Constructor ******************************/
MergeSort::MergeSort()
{
	arr = NULL;
	size = 0;
	npop = true;
	nsort = false;
}

MergeSort::~MergeSort()
{
	if(!npop)			//if an array has been populated
		delete arr;		//delete the array
}

void MergeSort::Populate(const int org[], const int &orgSize)
{
	if(npop)
	{
		arr = new int [orgSize];
		size = orgSize;

		for(int i = 0; i < size; i++)
			arr[i] = org[i];

		nsort = true;
		npop = false;
	}
}

void MergeSort::Sort()
{
	if(nsort)
	{
		//Merge Sort algorithm copied
		//from Data Abstraction and Problem Solving with C++
		//By Frank M. Carrano
		//Page 467-8
		
		stats.time_tracker.Start();

		Msort(arr, 0, size-1);

		stats.time_tracker.Stop();
		stats.time_tracker.CalculateLapse();
		nsort = false;
	}
}

int MergeSort::Size() const
{
	return size;
}

int MergeSort::operator [](const int index) const
{
	int rv;
	(index < 0 || index >= size) ? rv = -1  : rv = arr[index];
	return rv;
}

void MergeSort::Merge(int theArray[], int first, int mid, int last)
{
	int *tempArray = new int [size],
		first1 = first,
		last1 = mid,
		first2 = mid+1,
		last2 = last,
		index = first1;

	for(;(first1 <= last1) && (first2 <= last2); ++index)
	{
		if(theArray[first1] < theArray[first2])
		{
			tempArray[index] = theArray[first1];
			++first1;
		}
		else
		{
			tempArray[index] = theArray[first2];
			++first2;
		}
		stats.counter++;
	}

	for(;first1 <= last1; ++first1, ++index)
		tempArray[index] = theArray[first1];

	for(;first2 <= last2; ++first2, ++index)
		tempArray[index] = theArray[first2];

	for(index = first; index <= last; ++index)
		theArray[index] = tempArray[index];

	delete tempArray;
}

void MergeSort::Msort(int theArray[], int first, int last)
{
	if(first < last)
	{
		int mid = (first + last)/2;
		Msort(theArray, first, mid);
		Msort(theArray, mid+1, last);
		Merge(theArray, first, mid, last);
	}
}