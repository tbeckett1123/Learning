/*
Programmer:	Timothy Beckett
Class:		CSCI 3110
Instructor:	Dr. Seo
*/
# include "LinkedList.h"

#ifndef IMPLINKEDLIST_CPP
#define IMPLINKEDLIST_CPP

//default construstor
template <typename T>
LinkedList<T>::LinkedList()
{
	root = NULL;
	nodeCnt = 0;
}//end default constructor

//copy constructor
template <typename T>
LinkedList<T>::LinkedList(LinkedList<T> & org)
{
	Node<T> *mover, *last, *copier;
	
	if(org.root == NULL)		//if list is empty
	{
		root == NULL;			//set up a empty copy
		nodeCnt = 0;
	}//end if
	else						//copy list
	{
		nodeCnt = 0;			//node count

		mover = org.root;		//mover = root of orginal list

		copier = root = new Node<T>();  //start new list

		copier->data = mover->data;		//copy data

		nodeCnt++;						//increase node count
		
		while(mover->next != NULL)		//while there is another node
		{
			mover = mover->next;		//move to next node
			last = copier;				//last is end of new list
			copier = new Node<T>();		//create a new node
			nodeCnt++;					//increase node count
			last->next = copier;		//put node at end of new list
			copier->data = mover->data;	//copy data to last node
		}//end while
		
		copier->next = NULL;			//null terminate end of list
	}//end else
}//end copy constructor

//destructor
template <typename T>
LinkedList<T>::~LinkedList()
{
	Node<T> *selected = NULL;
	
	while(root != NULL)
	{
		selected = root;	//select node for deletion
		root = root->next;	//establish new root
		delete selected;	//delete selected node
	}//end while 

}//end destructor

template <typename T>
bool LinkedList<T>::isEmpty() const
{
	if(root == NULL)
		return false;

	return true;
}//end isEmpty

template <typename T>
int LinkedList<T>::size() const
{
	return nodeCnt;
}//end size

template <typename T>
bool LinkedList<T>::ins(const T& item, const int& index)
{
	Node<T> *cur, *last;
	
	if(index < 0 || index > (nodeCnt))//is index out of range
		return false;
	
	
	if(index == 0)
	{//case change root
		
		cur = new Node<T>(); //create new node
		cur->next = root;	//point cur at old root
		cur->data = item;	
		root = cur;			//change root
		nodeCnt++;
	}
	else if(index == nodeCnt)
	{//case change the end of list
		
		cur = new Node<T>();	//create new node
		cur->data = item;
		cur->next = NULL;		//create end of list signal
		
		for(last = root; last->next != NULL; last = last->next);  //find end of list
		
		last->next = cur;  //insert new node

		nodeCnt++;		//increment node count
		
	}
	else
	{
	//case insert node elsewhere in the list
		
		cur = root->next;
		last = root;
		
		//find insertion point
		for(int findIndex = 1; findIndex != index; findIndex++)
		{  
			last = cur;
			cur = cur->next;
		}//end for loop

		cur = new Node<T>();	//create new node
		cur->data = item;		
		
		cur->next = last->next; //insert node into list
		last->next = cur;
		
		nodeCnt++;				//increment node count
	}//end switch

	return true;
}//end insert method

template <typename T>
bool LinkedList<T>::rem(const int & index)
{
	Node<T> *cur, *last;

	if(index < 0 || index > (nodeCnt-1))//is index out of range
		return false;

	if(index == 0)
	{//case delete root
		cur = root;	//selecting node for deletion
		
		root = root->next; //marking new root
		
		delete cur;	//delete selected node

		nodeCnt--; //decrement node count

	}
	else if(index == nodeCnt-1)
	{//case delete end of list 
		
		//find end of list
		for(cur = root; cur->next != NULL; last = cur, cur = cur->next);

		last->next = NULL;  //mark new end of list

		delete cur;	//delete desired node

		nodeCnt--; //decrement node count

	}
	else
	{//delete a node else where in the list
		
		cur = root->next;
		last = root;
		
		//find deletion point
		for(int findIndex = 1; findIndex != index; findIndex++)
		{  
			last = cur;
			cur = cur->next;
		}//end for loop

		//remove selected node from the list
		last->next = cur->next;

		//delete node
		delete cur;

		nodeCnt--;

	};//end switch

	return true;
}//end of rem method

//get item method
template <typename T>
bool LinkedList<T>::get(T& item, int& index)
{
	if(index < 0 || index > nodeCnt-1)  //is index out of range
		return false;

	Node<T> *cur = root;
	int findIndex;

	//find desired node
	for(findIndex = 0; findIndex != index; findIndex++, cur = cur->next);

	item = cur->data;	//put data in refernce variable

	return true;

}//end get item method

//get index method
template <typename T>
bool LinkedList<T>::get(int& ptrIndex, T& item)
{
	Node<T> *cur = root;
	int index = 0;
	bool found = false;

	while(cur != NULL && !found)
	{
		if(*item == *(cur->data))
			found = true;

		if(!found) 
		{
			index++;

			cur = cur->next;
		}
	}//end while loop
	
	if(found)
	{
		ptrIndex = index;
		return found;
	}

	return found;

}//end get index method

# endif