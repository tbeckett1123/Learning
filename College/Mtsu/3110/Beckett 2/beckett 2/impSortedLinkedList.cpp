/*
Programmer:	Timothy Beckett
File:		Person.h -- Person Class
Class:		CSCI 3110
Instructor:	Dr. Seo
*/

# include "SortedLinkedList.h"
# include "impLinkedList.cpp"

# ifndef IMPSORTEDLINKEDLIST_CPP
# define IMPSORTEDLINKEDLIST_CPP

// * * * * Constructors * * * *

//copy constructor
template <typename T>
SortedLinkedList<T>::SortedLinkedList(SortedLinkedList<T> & org): LinkedList<T>(org)
{/*using constructor from LinkedList*/}//end copy constructor

//default construstor
template <typename T>
SortedLinkedList<T>::SortedLinkedList()  
{/*using constructor from LinkedList*/}//end default constructor

// * * * * Destructor * * * *

template <typename T>
SortedLinkedList<T>::~SortedLinkedList()
{/* using destructor from LinkedList*/}//end destructor

// * * * * Class Methods * * * *

//This method insert the data  into the list
template <typename T>
void SortedLinkedList<T>::ins(const T& data)
{
	int index = 0;

	Node<T>* finder;

	finder = root;

	//find location to insert
	while(finder != NULL && !(*data < *(finder->data)))
	{
		finder = finder->next;
		index++;
	}
	
	//insert with parent insert method
	LinkedList<T>::ins(data, index);
}//end ins

# endif