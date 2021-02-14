/*
Programmer:		Timothy Beckett
Class:			CSCI 3110
Instructor:		Dr. Seo
File:			impRBT.cpp
*/
# include "rbt.h"
# ifndef IMPRBT_CPP
# define IMPRBT_CPP


/*************** Constructors *****************/
template <typename U>
RBT<U>::RBT()
{
	root = NULL;
}

template <typename U>
RBT<U>::RBT(const RBT<U> &org)
{
	copy(root, org.root);
}

template <typename U>
RBT<U>::~RBT()
{
	Node<U> *mover = root;

	if(mover !=	NULL)
	{
		rem(mover->left);  //delete left child
		rem(mover->right); //delete right child
	}
	else
		return;  //mover is null quit operation;
	
	//returning from recursive call root is not null
	delete mover;	
}

/*********** Private Methods *************/
template <typename U>
void RBT<U>::write(Node<U> *mover, ofstream& out)
{
	if(mover == NULL)
		return;

	write(mover->left, out);
	out<<mover->data;
	write(mover->right, out);
}

template <typename U>
void RBT<U>::writet(Node<U>* mover, ofstream& out, int number)
{
	static string color;
	
	if(mover == NULL)
		return;

	writet(mover->left, out, number+1);
	
	(mover->color == Node<U>::black) ? color = "black " : color = "red ";
	
	out<<setfill('-')<<setw(number*10)<<color<<endl;

	writet(mover->right, out, number+1);
}

template <typename U>
void RBT<U>::rem(Node<U>* mover)
{
	if(mover !=	NULL)
	{
		rem(mover->left);  //delete left child
		rem(mover->right); //delete right child
	}
	else
		return;  //mover is null quit operation;
	
	//returning from recursive call mover is not null
	delete mover;
}

template <typename U>
void RBT<U>::copy(Node<U> *copier, Node<U>* org)
{
	if(org != NULL)
	{
		copier = new Node();
		copier->data = org->data;
		copier->color = org->color;
		copy(copier->left, org->left);
		copy(copier->right, org->right);
		return;
	}

	copier = NULL;
}

template <typename U>
void RBT<U>::rotate(Node<U> *ggParent, Node<U> *gParent, Node<U> *parent, Node<U> *current)
{
	//If both parent and current are leftchild
	if(
			gParent->left == parent
		&&	parent->left == current
	  ) //then
			llRotate(ggParent, gParent, parent, current);
	
	//parent is left child and current is a right child
	else if(
				gParent->left == parent
			&&	parent->right == current
			)//then
				lrRotate(ggParent, gParent, parent, current);

	//parent is a right child and current is a left child
	else if(
				gParent->right == parent
			&&	parent->left == current
		   )//then
				rlRotate(ggParent, gParent, parent, current);

	//parent and current are both right childern
	else
		rrRotate(ggParent, gParent, parent, current);

}

template <typename U>
void RBT<U>::llRotate(Node<U> *ggParent, Node<U> *gParent, Node<U> *parent, Node<U> *current)
{
	gParent->left = parent->right;
	parent->right = gParent;

	//if root, reattacht to the root
	if(gParent == root)
		root = parent;
	//reattach to the great-grandparent
	else
	{
		if(parent->data < ggParent->data)
			ggParent->left = parent;
		else
			ggParent->right = parent;
	}

	//color appropriately
	current->color	= Node<U>::red;
	parent->color	= Node<U>::black;
	gParent->color	= Node<U>::red;
}

template <typename U>
void RBT<U>::lrRotate(Node<U> *ggParent, Node<U> *gParent, Node<U> *parent, Node<U> *current)
{
	parent->right = current->left;
	current->left = parent;
	gParent->left = current->right;
	current->right = gParent;

	//if root, reattach to the root
	if(gParent == root)
		root = current;
	//reattach to the great-grandparent
	else
	{
		if(current->data < ggParent->data)
			ggParent->left = current;
		else
			ggParent->right = current;
	}

	//color appropriately
	current->color = Node<U>::black;
	parent->color = Node<U>::red;
	gParent->color = Node<U>::red;
}

template <typename U>
void RBT<U>::rlRotate(Node<U> *ggParent, Node<U> *gParent, Node<U> *parent, Node<U> *current)
{
	current->left = gParent;
	current->right = parent;
	gParent->right = parent->left = NULL;

	if(gParent == root)
	{
		root == current;
	}
	else
	{
		if(current->data < ggParent->data)
			ggParent->left = current;
		else
			ggParent->right = current;
	}

	//color appropriately
	parent->color	=	//black
	gParent->color	=	//black
	ggParent->color = Node<U>::black;
	current->color	= Node<U>::red;
}

template <typename U>
void RBT<U>::rrRotate(Node<U> *ggParent, Node<U> *gParent, Node<U> *parent, Node<U> *current)
{

	gParent->left = parent->left;
	gParent->right = NULL;
	parent->left = gParent;


	if(gParent == root)
	{
		root == current;
	}
	else
	{
		if(parent->data < ggParent->data)
			ggParent->left = parent;
		else
			ggParent->right = parent;
	}

	current->color = Node<U>::red;
	parent->color = Node<U>::black;
	gParent->color = Node<U>::red;

}


template <typename U>
void RBT<U>::preorder(Node<U>* current)
{
	if(current != NULL)
	{
	cout<<current->data<<endl;
	preorder(current->left);
	preorder(current->right);
	}
}

template <typename U>
void RBT<U>::postorder(Node<U>* current)
{
	if(current != NULL)
	{
		postorder(current->left);
		postorder(current->right);
		cout<<current->data<<endl;
	}
}

template <typename U>
void RBT<U>::inorder(Node<U> *current)
{
	if(current != NULL)
	{
		inorder(current->left);
		if(count > 20)
		{
			system("pause");
			system("cls");
			count = 0;
		}
		count++;
		cout<<current->data<<endl;
		inorder(current->right);
	}
}

/*********** Public Methods **************/
template <typename U>
void RBT<U>::Preorder()
{
	if(root != NULL)
	{
	cout<<root->data<<endl;
	preorder(root->left);
	preorder(root->right);
	}
}

template <typename U>
void RBT<U>::Postorder()
{
	if(root != NULL)
	{
		postorder(root->left);
		postorder(root->right);
		cout<<root->data<<endl;
	}
}

template <typename U>
void RBT<U>::Inorder()
{
	count = 0;
	if(root != NULL)
	{
		inorder(root->left);
		if(count > 20)
		{
			system("pause");
			system("cls");
			count = 0;
		}
		count++;
		cout<<root->data<<endl;
		inorder(root->right);
	}
}

template <typename U>
void RBT<U>::Ins(U & data)
{
	Node<U> *current, *parent, *gParent, *ggParent;

	current = parent = gParent = ggParent = root;

	if(root == NULL)
	{//a
		root = new Node<U>();
		root->data = data;
		root->left = root->right = NULL;
		root->color = Node<U>::black;
	}
	else
	{	
		while(current != NULL)
		{//b
			if(
					current->left != NULL 
				&&  current->right != NULL
				&&	current->left->color == Node<U>::red
				&&	current->right->color == Node<U>::red
			  )//then
			{
				//split 4-node
				//change colors and rotate approriately
				//4-node has no parent
				if(
					ggParent == gParent
				&&	gParent == parent
				&&	parent == current
				)//then
				 //change root, left child, and right child to black
				current->left->color = current->color = current->right->color = Node<U>::black;
					
				//4-node has 2-node parent
				else if(
					parent->left->color  == Node<U>::black
				&&	parent->right->color == Node<U>::black
				)
				//invert parent's, left child's, and right child's color
				{
					current->left->color = current->right->color = Node<U>::black;
					current->color = Node<U>::red;
				}
				//4-node has a 3-node parent
				else
				{
					//case 1 & 4
					if(parent == gParent)
					{
						parent->left->color = parent->right->color = Node<U>::red;
						current->left->color = current->right->color = Node<U>::black;
					}
					//case 2
					else if(
								gParent->left == parent
							&&	parent->left == current
						    )
					{
						gParent->left = parent->right;
						parent->right = gParent;

						parent->right->color = parent->left->color = Node<U>::red;
						current->left->color = current->right->color = Node<U>::black;

						if(gParent == root)
							root = parent;
						else if(current->data < ggParent->data)
							ggParent->left = current;
						else
							ggParent->right = current;
					}
					//case 3
					else if(
								gParent->right == parent
							&&	parent->right == current
						    )
					{
						gParent->right = parent->left;
						parent->left = gParent;

						parent->left->color = parent->right->color = Node<U>::red;
						current->left->color = current->right->color = Node<U>::black;

						if(gParent == root)
							root = parent;
						else if(current->data < ggParent->data)
							ggParent->left = current;
						else
							ggParent->right = current;
					}
					//case 5
					else if(
								gParent->right == parent
							&&	parent->left == current
							)
					{
						parent->left = current->right;
						gParent->right = current->left;
						current->left = gParent;
						current->right = parent;

						if(gParent == root)
							root = current;
						else if(current->data < ggParent->data)
							ggParent->left = current;
						else
							ggParent->right = current;

						current->left->color = current->right->color = Node<U>::red;
						parent->left->color = parent->right->color =
						gParent->left->color = gParent->right->color = Node<U>::black;
					}
					//case 6
					else
					{
						gParent->left = current->right;
						parent->right = current->left;
						current->right = gParent;
						current->left = parent;

						if(gParent == root)
							root = current;
						else if(current->data < ggParent->data)
							ggParent->left = current;
						else
							ggParent->right = current;

						current->left->color = current->right->color = Node<U>::red;
						parent->left->color = parent->right->color =
						gParent->left->color = gParent->right->color = Node<U>::black;
					}
				}
			}
			else //if you don't encournter a 4-node
			{
				//update pointers
				ggParent = gParent;
				gParent = parent;
				parent = current;
			}
			
			if(data < current->data)
				current = current->left;
			else
				current = current->right;
		}//end b

		//create a new node and enter the new data
		current = new Node<U>();
		current->data = data;
		current->left = current->right = NULL;
		current->color = Node<U>::red;


		
		//Attach the node to the tree
		if(parent->data > current->data)
			parent->left = current;
		else
			parent->right = current;
		
		//If two consecutive red edges are detected, then rotate
		if( 
			parent->color == Node<U>::red
		&&	current->color == Node<U>::red
		)
			rotate(ggParent, gParent, parent, current);
	}//end a
}//end Ins

template <typename U>
U& RBT<U>::Ret(U & key)
{
	Node<U>* mover = root;
	
	while(
				mover != NULL 
			&&	mover->data != key
		 )//do
			if(mover->data < key)
				mover = mover->right;
			else
				mover = mover->left;

	if(mover == NULL)
		return dummy;
	else
	{
		return mover->data;
	}
}

template <typename U>
void RBT<U>::Write(const string& fileName)
{
	ofstream fOut;

	fOut.open(fileName.c_str());
	
	write(root, fOut);

	fOut.close();

	fOut.clear();

	fOut.open("tree.dat");

	writet(root, fOut, 0);

	fOut.close();

	cout<<"The data from the tree has been written to "<<fileName<<endl
		<<"The tree structure has been written to tree.dat\n";	
	
}
# endif