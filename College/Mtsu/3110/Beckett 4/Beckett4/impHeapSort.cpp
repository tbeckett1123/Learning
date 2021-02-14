/*
Programmer:		Timothy Beckett
Class:			CSCI 3110
Instructor:		Dr. Seo
File:			impHeapSort.cpp
*/

# include "HeapSort.h"

/********************** Friend Function ***************************/
ostream& operator<<(ostream& out, HeapSort& data)
{
	out <<setw(11)<<"Heap Sort"
		<<setw(5)<<data.size
		<<setw(5)<<data.stats.counter
		<<data.stats.time_tracker.TimeLapse()
		<<endl;

	return out;
}

/*********************** Constructor ******************************/
HeapSort::HeapSort()
{
	arr = NULL;
	size = 0;
	npop = true;
	nsort = false;
}

HeapSort::~HeapSort()
{
								//if an array has been populated
	if (!npop) delete arr;		//delete the array
}

void HeapSort::Populate(const int org[], const int &orgSize)
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

void HeapSort::Sort()
{
	if(nsort)
	{		
		stats.time_tracker.Start();
		
		//starting heapsort
		
		BuildHeap(arr, size);

		for(int i = size-1; i >= 1; i--)
		{
			swap(arr[i], arr[0]);
			Siftdown(arr, 0, i-1);
		}

		stats.time_tracker.Stop();
		stats.time_tracker.CalculateLapse();
		nsort = false;
	}
}

int HeapSort::Size() const
{
	return size;
}

int HeapSort::operator [](const int index) const
{
	int rv;
	(index < 0 || index >= size) ? rv = -1  : rv = arr[index];
	return rv;
}

void HeapSort::swap(int& one, int& two)
{
	int temp = one;
	one = two;
	two = temp;
}

void HeapSort::BuildHeap(int arr[], int n)
{
	for(int i = (n/2)-1; i >= 0; i--)
		Siftdown(arr, i, n);	
}

void HeapSort::Siftdown(int numbers[], int root, int bottom)
{
	int done, maxChild;

	done = 0;
	while((root*2) <= bottom && (!done))
	{
		if(root*2 == bottom)
			maxChild = root * 2;
		else if (numbers[root*2] > numbers[root * 2 + 1])
		{
			stats.counter++;
			maxChild = root * 2;
		}
		else
		{
			stats.counter++;
			maxChild = root * 2 + 1;
		}
		
		stats.counter++;
		if (numbers[root] < numbers[maxChild])
		{
			swap(numbers[root], numbers[maxChild]);
			root = maxChild;
		}
		else
			done = 1;
	}
}