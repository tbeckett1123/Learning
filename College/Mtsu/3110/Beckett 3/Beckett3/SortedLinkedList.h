/*
Programmer:	Timothy Beckett
Class:		CSCI 3110
File:		SortedLinkedList.h`
Instructor:	Dr. Seo
*/

# include <iostream>
# include <list>

using namespace std;

#ifndef SORTEDLINKEDLIST_H
#define SORTEDLINKEDLIST_H

template <typename T>
class SortedLinkedList: protected list<T>
{
public:
	/*
	defualt constructor

	The default constructor will set the root
	node to NULL and nodeCnt to 0
	
	Preconditions:	None
	Postconditions:	None
	*/
	SortedLinkedList();

	/*
	copy constructor

	The copy constructor will make this object
	to be an exact copy of the provide object.

	Preconditions:	The user must provide a Linked
					List object to be copied
	Postconditions:	This Linked List object will be
					an exact copy of the provided one
	*/
	SortedLinkedList(SortedLinkedList<T> &);

	/*
	destructor

	The destructor will destroy the linked list.
	It will clean up any dynamicly allocated
	memory used by the object.

	Preconditions:	None
	Postconditions:	The List will be destroyed
					and all dynamicly allocated
					memory will be returned to
					the system.
	*/
	~SortedLinkedList();

	/*
	This method will report if the list is empty

	Preconditions:	None
	Postconditions:	The method will return a boolean
					true if there is no data in the 
					list otherwise it will return 
					a boolean false.
	*/
	bool isEmpty() const;

	/*
	This method will return the number of items in the
	list.

	Preconditions:	None
	Postconditions:	The method will return the number of
					item in a list.  The data type will
					be an int.
	*/
	int Size() const;

	/*
	This method will insert an item into the list at
	the desired index point.

	Preconditions:	The user must provide the data
					to be inserted.
	Postconditions:	The method will return true
					and increment the sizeCnt, if
					the operation was successful
					otherwise it will return false
	*/
	void ins(T&);

	/*
	This method will remove the i-th node from the list
	and clean up the used memory.

	Preconditions:	the user must provide the index number
					of the item to be removed.
	NOTE:			0 indexes the first item in the list,
					1 indexes the second item in the list, etc.
	Postconditions:	if the operation is successful this method
					will return a boolean true, and sizeCnt will
					be decremented otherwise the method	will 
					return a boolean false.
	*/
	void rem(const T&);

	/*
	This method will retreive the record from the desired
	index number.

	Preconditions:	The user must provide a variable of the data
					type and the index number in that order.
					This method assumes that the = operator has
					been overloaded
	NOTE:			0 indexes the first item in the list,
					1 indexes the second item in the list, etc.
	Postcoditions:	if a copy of the record will be place in the 
					provided variable, and the method will return
					a boolean true.  
					If the index provided is invalid, the method
					will return a boolean false, and the value of
					the provided variable will remain unchanged.
	*/
	bool get(T&, int &);

	/*
	This method will determine if the disired record is in the list.
	If it is the index number will be place in the provided variable.

	Preconditions:	The user must provide a integer variable for the
					index to be place in, and copy of the desired data
	Postconditions:	If the record is in the list, the index number will
					be put in the provide integer, and the method will
					return a boolean true otherwise the method will 
					return a boolean false and the provided variable
					will be unchanged.
	*/
	bool get(int&, T&);
};

#endif