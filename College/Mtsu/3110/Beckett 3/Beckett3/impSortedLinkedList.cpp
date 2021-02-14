/*
Programmer:	Timothy Beckett
Class:		CSCI 3110
File:		impSortedLinkedList.cpp
Instructor:	Dr. Seo
*/
# include "SortedLinkedList.h"

#ifndef IMPSORTEDLINKEDLIST_CPP
#define IMPSORTEDLINKEDLIST_CPP

//default construstor
template <typename T>
SortedLinkedList<T>::SortedLinkedList()
{
}//end default constructor

//copy constructor
template <typename T>
SortedLinkedList<T>::SortedLinkedList(SortedLinkedList<T> & org): list<T>(org)
{
	/*int i;
	T temp;
	
	for(int j = 0; j < org.Size(); j++)
	{
		SortedLinkedList::get(temp, i);
		push_back(temp);
	}

	sort();*/
}//end copy constructor

//destructor
template <typename T>
SortedLinkedList<T>::~SortedLinkedList()
{
	clear();
}//end destructor

template <typename T>
bool SortedLinkedList<T>::isEmpty() const
{
	return (size() == 0);
}//end isEmpty

template <typename T>
int SortedLinkedList<T>::Size() const
{
	return size();
}//end size

template <typename T>
void SortedLinkedList<T>::ins(T& item)
{
	list::iterator mover;
	
	int i;


	if(isEmpty())
		insert(begin(), item);
	else
	{
		for(i  = 0, mover = begin(); i < Size() && !(**mover < *item); mover++, i++);

		insert(mover, item);
	}

}//end insert method

template <typename T>
void SortedLinkedList<T>::rem(const T& item)
{
	remove(item);
}//end of rem method

//get item method
template <typename T>
bool SortedLinkedList<T>::get(T& item, int& index)
{
	list<T>::iterator slider;

	if(index > size() || index < 0)
		return false;

	slider = begin();

	for(int i = 0; i <= index; i++, slider++)
		item = *slider;

	return true;
}//end get item method

//get index method
template <typename T>
bool SortedLinkedList<T>::get(int& ptrIndex, T& item)
{
	list<T>::iterator curr;

	curr = begin();
	
	for(ptrIndex = 0; ptrIndex < Size() && !(*item == **curr); ptrIndex++, curr++);
		
	return (*item == **curr);
	
}//end get index method

# endif