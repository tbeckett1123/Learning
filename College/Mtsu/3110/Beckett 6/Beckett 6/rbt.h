/*
Programmer:		Timothy Beckett
Class:			CSCI 3110
Instructor:		Dr. Seo
File:			rbt.h
*/

# include <iostream>
# include <fstream>
# include <iomanip>

using namespace std;

# ifndef RBT_H
# define RBT_H

template <typename T>
struct Node
{
	T		data;
	Node	*left,
			*right;
	enum Color {black, red} color;
};

template <typename U>
class RBT
{
public:
	
	RBT();				//Default constructor
						//Precodintions None
						//Postcondtions root = NULL and size = 0

	RBT(const RBT<U>&);			//Copy constructor
								//Preconditions	Must provide a BST<U>
								//Postcontions	A deep copy of the BST<U>
								//				provided will be made

	~RBT();						//Destructor
								//Precondtions	NA
								//Postcondtions	NA

	void Ins(U&);				//Calls the private ins method to insert
								//an item to the tree
								//Precondtions	The user must provide the
								//				data to be inserted
								//Poscondtions	A node will be insert into
								//				the tree containing the 
								//				provided data

	U&	 Ret(U&);				//Searches the tree based on the provided key
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
						

	void Preorder();			//Prints to the screen a Preorder traveral
								//Precondtions	none
								//Postcondtions	none
	void Postorder();			//Prints to the screen a Postorder traveral
								//Precondtions	none
								//Postcondtions	none
	void Inorder();				//Prints to the screen a Inorder traveral
								//Precondtions	none
								//Postcondtions	none
	void Write(const string &);	//it writes tree to a provide data file name and
								//it writes the tree structure to tree.dat
								//Precondtions	user must provide a string that
								//				is the name of the data file to
								//				be written to.
								//Postcondtions	The provided file will be written over
								//				a data file call tree.dat will contain
								//				the structure of the tree.

private:

	void preorder(Node<U>*);	//used by Preorder and preorder
	void postorder(Node<U>*);	//used by Postorder and postorder
	void inorder(Node<U>*);		//used by Inorder and inorder
	
	void copy(Node<U>*, Node<U>*); //used by copy constructor

	void write(Node<U>*, ofstream&);	//used to write the tree data to file
	void writet(Node<U>*, ofstream&, int);	//used to write the tree structure to file
	
	void rotate(Node<U>*, Node<U>*, Node<U>*, Node<U>*);	//used by Ins
	
	//these are used by rotate
	void llRotate(Node<U>*, Node<U>*, Node<U>*, Node<U>*);
	void lrRotate(Node<U>*, Node<U>*, Node<U>*, Node<U>*);
	void rlRotate(Node<U>*, Node<U>*, Node<U>*, Node<U>*);
	void rrRotate(Node<U>*, Node<U>*, Node<U>*, Node<U>*);
	
	void rem(Node<U>*); //used by destructor

	Node<U>* root;
	U dummy;
	int count;
};
# endif