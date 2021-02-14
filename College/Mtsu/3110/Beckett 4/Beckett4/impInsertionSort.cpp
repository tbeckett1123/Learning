/*
Programmer:		Timothy Beckett
Class:			CSCI 3110
Instructor:		Dr. Seo
File:			impInsertionSort.cpp
*/

# include "InsertionSort.h"

/********************** Friend Function ***************************/
ostream& operator<<(ostream& out, InsertionSort& data)
{
	out <<setw(11)<<"Insertion Sort"
		<<setw(5)<<data.size
		<<setw(5)<<data.stats.counter
		<<data.stats.time_tracker.TimeLapse()
		<<endl;

	return out;
}

/*********************** Constructor ******************************/
InsertionSort::InsertionSort()
{
	arr = NULL;
	size = 0;
	npop = true;
	nsort = false;
}

InsertionSort::~InsertionSort()
{
	if(!npop)			//if an array has been populated
		delete arr;		//delete the array
}

void InsertionSort::Populate(const int org[], const int &orgSize)
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

void InsertionSort::Sort()
{
	if(nsort)
	{
		//Insertion Sort algorithm copied
		//from Data Abstraction and Problem Solving with C++
		//By Frank M. Carrano
		//Page 464-5
		
		stats.time_tracker.Start();

		for(int unsorted = 1; unsorted < size; ++unsorted)
		{
			int nextItem = arr[unsorted];
			int loc = unsorted;

			for(; (loc > 0) && (arr[loc-1]>nextItem); --loc)
			{
				stats.counter++;
				arr[loc]= arr[loc-1];
			}
			stats.counter++;
			arr[loc] = nextItem;
		}

		stats.time_tracker.Stop();
		stats.time_tracker.CalculateLapse();
		nsort = false;
	}
}

int InsertionSort::Size() const
{
	return size;
}

int InsertionSort::operator [](const int index) const
{
	int rv;
	(index < 0 || index >= size) ? rv = -1  : rv = arr[index];
	return rv;
}