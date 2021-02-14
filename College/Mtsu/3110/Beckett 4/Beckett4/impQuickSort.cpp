/*
Programmer:		Timothy Beckett
Class:			CSCI 3110
Instructor:		Dr. Seo
File:			impQuickSort.cpp
*/

# include "QuickSort.h"

/********************** Friend Function ***************************/
ostream& operator<<(ostream& out, QuickSort& data)
{
	out <<setw(11)<<"Quick Sort"
		<<setw(5)<<data.size
		<<setw(5)<<data.stats.counter
		<<data.stats.time_tracker.TimeLapse()
		<<endl;

	return out;
}

/*********************** Constructor ******************************/
QuickSort::QuickSort()
{
	arr = NULL;
	size = 0;
	npop = true;
	nsort = false;
}

QuickSort::~QuickSort()
{
	if(!npop)			//if an array has been populated
		delete arr;		//delete the array
}

void QuickSort::Populate(const int org[], const int &orgSize)
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

void QuickSort::Sort()
{
	if(nsort)
	{
		//Quick Sort algorithm copied
		//from Data Abstraction and Problem Solving with C++
		//By Frank M. Carrano
		//Page 478-9

		stats.time_tracker.Start();

		quicksort(arr, 0, size-1);

		stats.time_tracker.Stop();
		stats.time_tracker.CalculateLapse();
		nsort = false;
	}
}

int QuickSort::Size() const
{
	return size;
}

int QuickSort::operator [](const int index) const
{
	int rv;
	(index < 0 || index >= size) ? rv = -1  : rv = arr[index];
	return rv;
}

void QuickSort::partition(int theArr[], int first, int last, int &pivotIndex)
{
	int pivot = theArr[first];

	int lastS1 = first;
	int firstUnknown = first + 1;
	int temp;

	for(; firstUnknown <= last; ++firstUnknown)
	{
		if(theArr[firstUnknown] < pivot)
		{
			++lastS1;

			swap(theArr[firstUnknown], theArr[lastS1]);	
		}
		stats.counter++;
	}

	swap(theArr[first], theArr[lastS1]);

	pivotIndex = lastS1;

}

void QuickSort::quicksort(int theArr[], int first, int last)
{
	int pivotIndex;

	if(first < last)
	{
		partition(theArr, first, last, pivotIndex);

		quicksort(theArr, first, pivotIndex-1);
		quicksort(theArr, pivotIndex+1, last);
	}
}

void QuickSort::swap(int& one, int& two)
{
	int temp = one;
	one = two;
	two = temp;
}