/*
Programmer:	Timothy Beckett
File:		Person.h -- Person Class
Class:		CSCI 3110
Instructor:	Dr. Seo
*/

# include "LinkedList.h"

# ifndef SORTEDLINKEDLIST_H
# define SORTEDLINKEDLIST_H

//ADT available from the LinkedList<T>
/*************************************
template<typename T>
struct Node
{
		T		data;
		Node	*next;
};
*************************************/

template <typename T>
class SortedLinkedList: public LinkedList<T>
{
public:
// * * * * Constructors * * * *
	//copy construcotor
	SortedLinkedList(SortedLinkedList<T>&);

	//default constructor
	SortedLinkedList();

// * * * * Destructor * * * *
	
	~SortedLinkedList();

// * * * * Class Methods * * * *

	/*
	This method will insert the data into the list
	in increasing or alaphbetical order.

	Preconditions:	The calling fucntion must provide
					the data of type T
	Postconditions:	The data will be inserted into the
					list into the list
	*/
	void ins(const T&);

// * * * * Methods Available from LinkedList Class * * * *
/*	
	********* bool isEmpty() const; ************
	This method will report if the list is empty

	Preconditions:	None
	Postconditions:	The method will return a boolean
					true if there is no data in the 
					list otherwise it will return 
					a boolean false.
	************************************************
	
	*********** int size() const; ********************
	This method will return the number of items in the
	list.

	Preconditions:	None
	Postconditions:	The method will return the number of
					item in a list.  The data type will
					be an int.
	****************************************************
	
	************** bool rem(const int &); *************
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
	****************************************************

	**************** bool get(T&, int &); ***************
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
	************************************************************

	******************** bool get(int&, T&); ***********************
	This method will determine if the disired record is in the list.
	If it is the index number will be place in the provided variable.

	Preconditions:	The user must provide a integer variable for the
					index to be place in, and copy of the desired data
	Postconditions:	If the record is in the list, the index number will
					be put in the provide integer, and the method will
					return a boolean true otherwise the method will 
					return a boolean false and the provided variable
					will be unchanged.
	*****************************************************************

	***********Private Data Members of LinkedList Class**************
	***********Available to SortedLinkedList*************************

	   ************************************
	   WARNING BE CAUTOUS OF CHANGING THESE
	   VARIABLES USE PREDEFINED MEMBER 
	   METHODS FROM LINKED LIST
	   ************************************

	Node<T> *root	Points to the front of the list
	int		nodeCnt Keeps track of the number of nodes
	

	*****************************************************************
*/
};

# endif