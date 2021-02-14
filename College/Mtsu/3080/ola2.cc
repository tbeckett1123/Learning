/* * * * * * * * * * * * * * * * * * * * * * *
 * 					     *
 * Author:	Timothy Beckett              *
 * Instructor:	C. Pettey		     *
 * Class:	CSCI 3080		     *
 * Program:	Open Lab 2		     *
 * Date Due:	10-20-05 		     *
 * Purpose:	This program will read in    *
 *		the data for a ternary tree  *
 *		(It can only represent whole *
 *		numbers greater than zero    *
 *		and it has a ten node limit) *
 *		After it contructs the sim-  *
 *		mulated tree and adjacency   *
 *		matrix, it will print the    *
 *		two to the screen along with *
 *		the preorder, inorder, and   *
 *		post order traversals of the *
 *		tree                         *
 * * * * * * * * * * * * * * * * * * * * * * */

# include <iomanip>
# define MAX_SIZE 10
# define null -1

using namespace std;

struct node
{
	int 	data,		//data of node
		lft,		//represents lft, mid,
		mid,		// & rght child pointers
		rght;		
};

unsigned int build_tree(node[], int[][MAX_SIZE]);
void print_data(const node[], const int [][MAX_SIZE], const unsigned int &);
void preorder_traverse(const node[], const int &);
void inorder_traverse(const node[], const int &);
void postorder_traverse(const node[], const int &);

int main()
{
	node tree[MAX_SIZE];
	/* tree
	   limitations:  this tree can only represent int's > 0
	   		 -1 is used to represent null or invalid
			 data
			 the tree size is 1 to MAX_SIZE
	*/
	
	unsigned int tree_size;
	
	int adjacency_matrix[MAX_SIZE][MAX_SIZE];
	
	/* intialize array
	   all data members are set to -1 to represent that
	   there is no tree 
	*/
	for(int i = 0; i < MAX_SIZE; i++)
	{
		tree[i].data = -1;
		tree[i].lft = null;
		tree[i].mid = null;
		tree[i].rght = null;
	}
	
	tree_size = build_tree(tree, adjacency_matrix);
	
	print_data(tree, adjacency_matrix, tree_size);
	
	cout	<<"The preorder traversal is:\n";	// 1 is the root node
	preorder_traverse(tree, 1);			// and should always
	cout	<<endl;					// be the 1st node
							// examined
	cout	<<"The inorder traversal is:\n";
	inorder_traverse(tree, 1);
	cout	<<endl;	
	
	cout	<<"The postorder traversal is: \n";
	postorder_traverse(tree, 1);
	cout	<<endl;	
	
	return 0;
}// end main()

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Purpose:		This function builds an array representation   *
 * 			of a ternary tree                              *
 *			it also produces the adjaceny matrix	       *
 * Note: 		Tree limitations as stated by tree declareation* 
 *			in main                                        *
 * Preconditions:	This function expects an array of node         *
 *			type.                                          *
 *			It also exepcts a 2d int array for the         *
 *			adjacency matrix			       *
 * Postconditions:	This function returns an unsigned int          *
 *			which is the tree size (number of nodes        *
 *			in the tree) 				       *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
unsigned int build_tree(node tmp_tree[], int adjacency_matrix[][MAX_SIZE])
{
	unsigned int tree_size, data;
	
	cout	<<"Please enter the tree's data as follows:\n"
		<<"The first number is the number of nodes in the tree.\n"
		<<"enter -1 to represent a null child ptr\n";
	
	cin	>>tree_size;			// reading in the number of
						// nodes in the tree
						
	while(tree_size > MAX_SIZE || tree_size < 1)
	{
		cerr	<<"< * * * Invalid Tree Size * * * >\n"
			<<"Please enter a tree size between 1 & "<<MAX_SIZE<<endl;
			
		cin	>>tree_size;
	}
	
	for(int i = 0; i < tree_size; i++)	// reading in each node
	{					
		cin	>>data;
		/*
		reading the node that is being focused on first always 
		the user the freedom to enter the nodes in any order
		desired as long as he/she lists the children next to it
		*/
		
		tmp_tree[data-1].data = data;
		
		cin	>>tmp_tree[data-1].lft
			>>tmp_tree[data-1].mid
			>>tmp_tree[data-1].rght;
	}
	
	// creating adjacency matrix
	for(int i = 0; i < tree_size; i++)
	{
		for(int j = 1; j <= tree_size; j++)
		{
			if(tmp_tree[i].lft == j || tmp_tree[i].mid == j || tmp_tree[i].rght == j)
				adjacency_matrix[i][j-1] = 1;
			else
				adjacency_matrix[i][j-1] = 0;
			// end if		
		}// end j loop
	}//end i loop
	
	return tree_size;
	
}// end build_tree()

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Purpose:		This function will print the left child, middle child, * 
 * 			right child array representaion and adjacency matrix   *
 *                      of a ternary tree                                      *
 * Preconditions:	This function expects you to pass an array of node     *
 *			type and a unsigned int which is the tree size	       *
 * Postconditions:	it prints the data to the screen		       *
 *			it has no return values				       *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void print_data(const node tmp_tree[], const int adjacency_matrix[][MAX_SIZE], const unsigned int & tree_size)
{
	cout	<<"The adjacency matrix is:\n";
	
	for(int i = 0; i < tree_size; i++)
	{
		for(int j = 0; j < tree_size; j++)
			cout	<<setw(4)<<adjacency_matrix[i][j];
		//end j loop
		
		cout	<<endl;
	}// end i loop

	cout	<<"The left child, middle child, right child array representation is:\n";
	
	for(int i = 0; i < tree_size; i++)
	{
		cout	<<setw(4)<<tmp_tree[i].lft
			<<setw(4)<<tmp_tree[i].mid
			<<setw(4)<<tmp_tree[i].rght
			<<endl;
	}
}// end print_data()

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Purpose:		These are recursive functions that traverse through*
 *			a ternary tree in a preorder, inorder, or postorder*
 *			fashion assuming, the first time one of these	   *
 *			functions is called, it receives the root node.    *
 * Preconditions:	These functions expect to receive an array of node *
 *			type and and int which is the node to be examined  *
 * Postconditions:	When the recursive algorythim is finished the      *
 *			preorder, inorder, or postorder traversal will be  *
 *			printed to the screen                              *
 *			These functions do not have return values          * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void preorder_traverse(const node tmp_tree[], const int  & next)
{
	if(next == null)  // when you reach a node child that is null stop 
		return;	  // traversing and return to calling function	
	
	cout<<setw(4)<<tmp_tree[next-1].data;		   // printing data in the node	
	preorder_traverse(tmp_tree, tmp_tree[next-1].lft); // moving to the left child
	preorder_traverse(tmp_tree, tmp_tree[next-1].mid); // moving to the middle child
	preorder_traverse(tmp_tree, tmp_tree[next-1].rght);// moving to the right child
}//end preorder_travers()
 
void inorder_traverse(const node tmp_tree[], const int & next)
{
	if(next == null)  // when you reach a node child that is null stop 
		return;	  // traversing and return to calling function	
	
	inorder_traverse(tmp_tree, tmp_tree[next-1].lft); // moving to the left child
	cout<<setw(4)<<tmp_tree[next-1].data;		  // printing data in the node
	inorder_traverse(tmp_tree, tmp_tree[next-1].mid); // moving to the middle child
	inorder_traverse(tmp_tree, tmp_tree[next-1].rght);// moving to the right child
}//end inorder_traverse()

void postorder_traverse(const node tmp_tree[], const int & next)
{
	if(next == null) // when you reach a node child that is null stop
		return;  // traversing and return to calling function
		
	postorder_traverse(tmp_tree, tmp_tree[next-1].lft); // moving to the left child
	postorder_traverse(tmp_tree, tmp_tree[next-1].mid); // moving to the middle child
	postorder_traverse(tmp_tree, tmp_tree[next-1].rght);// moving to the right child
	cout<<setw(4)<<tmp_tree[next-1].data;		    // print data in node
}//end postorder_traverse()

// ****** end of recursive traversal function *******
