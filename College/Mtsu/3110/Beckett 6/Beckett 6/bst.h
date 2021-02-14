/*
Programmer:		Timothy Beckett
Class:			CSCI 3110
Instructor:		Dr. Seo
File:			bst.h
*/

# include <iostream>

using namespace std;

# ifndef BST_H
# define BST_H

template <typename T>
struct Node
{
	T		data;
	Node	*left,
			*right;
};

template <typename U>
class BST
{
public:
	
	BST();				//default constructor
						//Precodintions None
						//Postcondtions root = NULL and size = 0

	BST(const BST<U>&);	//Copy constructor
						//Preconditions	Must provide a BST<U>
						//Postcontions	A deep copy of the BST<U>
						//				provided will be made

	void Ins(U&);	//Calls the private ins method to insert
						//an item to the tree
						//Precondtions	The user must provide the
						//				data to be inserted
						//Poscondtions	A node will be insert into
						//				the tree containing the 
						//				provided data

	void Rem(U&);	//Calls the private rem method to remove
						//an item from the list
						//Precondtions	The user must provide the
						//				Key to search for
						//Postcondtions	The Node containing the
						//				data will be removed from
						//				the tree and from memory

	U&	 Ret(U&); //Searches the tree based on the provided key
						//it will return the address of the data to be
						//edited. If the key isn't found it will return
						//a dummy value.
						//Preconditions	This method assumes that a default
						//				value is provided from a dnamyicly
						//				allocated memmory.  It assumes that
						//				the user will clean up the memory  
						//				to the dummy variable in the event
						//				that the key is not found.
						//Postcondtions	The address to the data matching the
						//				key will be returned for editing.
						//				if the value is not found it will 
						//				return a dynamicly allicated dummy value
						

	void Preorder();	//Prints to the screen a Preorder traveral
						//Precondtions	none
						//Postcondtions	none
	void Postorder();	//Prints to the screen a Postorder traveral
						//Precondtions	none
						//Postcondtions	none
	void Inorder();		//Prints to the screen a Inorder traveral
						//Precondtions	none
						//Postcondtions	none

private:

	void preorder(Node<U>*);
	void postorder(Node<U>*);
	void inorder(Node<U>*);

	void copy(Node<U>*, Node<U>*);

	void ins(Node<U>*, Node<U>*, U&);
	void rem(Node<U>*, Node<U>*, U&);
	void fix(Node<U>*);

	Node<U>* root;
	U dummy;
	int size, count;
};
# endif