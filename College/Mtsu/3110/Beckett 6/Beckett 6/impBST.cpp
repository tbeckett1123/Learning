/*
Programmer:		Timothy Beckett
Class:			CSCI 3110
Instructor:		Dr. Seo
File:			bst.cpp
*/
# include "bst.h"
# ifndef IMPBST_CPP
# define IMPBST_CPP


/*************** Constructors *****************/
template <typename U>
BST<U>::BST()
{
	root = NULL;
	size = 0;
}

template <typename U>
BST<U>::BST(const BST<U> &org)
{
	size = org.size;

	copy(root, org.root);
}

/*********** Private Methods *************/
template <typename U>
void BST<U>::copy(Node<U> *copier, Node<U>* org)
{
	if(org != NULL)
	{
		copier = new Node();
		copier->data = org->data;
		copy(copier->left, org->left);
		copy(copier->right, org->right);
		return;
	}

	copier = NULL;
}

template <typename U>
void BST<U>::preorder(Node<U>* current)
{
	if(current != NULL)
	{
	cout<<current->data<<endl;
	preorder(current->left);
	preorder(current->right);
	}
}

template <typename U>
void BST<U>::postorder(Node<U>* current)
{
	if(current != NULL)
	{
		postorder(current->left);
		postorder(current->right);
		cout<<current->data<<endl;
	}
}

template <typename U>
void BST<U>::inorder(Node<U> *current)
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

template <typename U>
void BST<U>::ins(Node<U> *current, Node<U> *previous, U &data)
{
	if(current != NULL)
	{
		if(current->data < data)
			ins(current->right, current, data);
		else
			ins(current->left, current, data);
		
		return;
	}

	current = new Node<U>();

	current->left = current->right = NULL;

	current->data = data;

	if(previous->data < current->data)
		previous->right = current;
	else
		previous->left = current;

	size++;
}

template <typename U>
void BST<U>::rem(Node<U> *current, Node<U>* previous, U& key)
{
	Node<U>* find, *last;

	if(current == NULL)
	{
		cout<<"Item not Found\n";
	}
	else if(current->data == key)
	{
		last = current;
		find = current->right;

		while(find != NULL)
		{
			last = find;
			find = find->left;
		}

		last->left = current->left;

		if(current->data < previous->data && current->right != NULL)
			previous->left = current->right;
		else if(current->data < previous->data)
			previous->left = current->left;
		else 
			previous->right = current->right;

		delete current;
	}
	else if(current->data < key)
		rem(current->right, current, key);
	else
		rem(current->left, current, key);
}

/*********** Public Methods **************/
template <typename U>
void BST<U>::Preorder()
{
	if(root != NULL)
	{
	cout<<root->data<<endl;
	preorder(root->left);
	preorder(root->right);
	}
}

template <typename U>
void BST<U>::Postorder()
{
	if(root != NULL)
	{
		postorder(root->left);
		postorder(root->right);
		cout<<root->data<<endl;
	}
}

template <typename U>
void BST<U>::Inorder()
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
void BST<U>::Ins(U & data)
{
	if(root != NULL)
	{
		if(root->data < data)
			ins(root->right, root, data);
		else
			ins(root->left, root, data);

		return;
	}

	root = new Node<U>();

	root->left = root->right = NULL;
	root->data = data;
	size++;
}

template <typename U>
void BST<U>::Rem(U & key)
{
	rem(root, root, key);
}

template <typename U>
U& BST<U>::Ret(U & key)
{
	Node<U>* mover = root;
	
	while(mover != NULL && mover->data != key)
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
# endif