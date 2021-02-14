/* * * * * * * * * * * * * * * * * * * * * * *
 * 					     *
 * Author:	Timothy Beckett              *
 * Instructor:	C. Pettey		     *
 * Class:	CSCI 3080		     *
 * Program:	Open Lab 1		     *
 * Date Due:	9-22-05 		     *
 * Purpose:	This program will read in    *
 *		two arrays no bigger than    *
 *		10x10 each.  It will then    *
 *		on request: determine whether* 
 *		the first  array is symmetric*
 *		, add the matrices together  *
 *		if possible, multiply the two*
 *		matrices together if possible*
 *		and determine the  transpose *
 *		of the first matrix and it   *
 *		will print the results       *
 * * * * * * * * * * * * * * * * * * * * * * */

# include <iostream>
# include <iomanip>

using namespace std;

struct matrix
{
	int arr[10][10];
	int rows;
	int cols;
};

void symmetric(matrix);
void addMatrices(matrix, matrix);
void multiplyMatrices(matrix, matrix);
void transpose(matrix);

int main()
{
	matrix first, second;
	char select;
	
	cout	<<"Welcome to the Matrix Calculator!\n"
		<<"Please enter the number of rows and the number of columns for the first matrix:\n";
	cin	>>first.rows>>first.cols;
	
	while(first.rows > 10 || first.cols > 10)
	{
		cout	<<"Invalid dimensions\n"
			<<"Please enter the number of rows and columns for the matrix:\n";
		cin	>>first.rows>>first.cols;
	}
	
	cout	<<"Please enter the first matrices' data:\n"
		<<"Enter the data by rows and then columns\n"
		<<"ex:\n"
		<<"1 2 3 4 5 6 7 8 9\n"
		<<"Row 1 row 2 row 3\n\n"
		<<"ex 2:\n"
		<<"1 2 3\n"
		<<"4 5 6\n"
		<<"7 8 9\n\n"; 
	
	// reading in the data for the first matrix
	for(int i = 0; i < first.rows; i++)
	{
		for(int j = 0; j < first.cols; j++)
			cin>>first.arr[i][j];
	}
	
	cout	<<"Please enter the number of rows and the number of columns for the second matrix:\n";
	cin	>>second.rows>>second.cols;
	
	while(second.rows > 10 || second.cols > 10)
	{
		cout	<<"Invalid dimensions\n"
			<<"Please enter the number of rows and columns for the matrix:\n";
		cin	>>second.rows>>second.cols;
	}

	cout	<<"Please enter the second matrices' data:\n";
	
	
	//reading in the data for the second matrix
	for(int i = 0; i < second.rows; i++)
	{
		for(int j = 0; j < second.cols; j++)
			cin>>second.arr[i][j];
	}
	
	do
	{
		cout	<<endl
			<<"1.	Determine whether the first matrix is symmetric\n"
			<<"2.	Add the two matrices and print the answer\n"
			<<"3.	Multiply the two matrices\n"
			<<"4.	Determine the traspose of the first matrix\n"
			<<"5.	Quit Processing\n"
			<<"Please enter your selection: ";
		
		cin	>>select;
		
		switch(select)
		{
			case '1': symmetric(first); 		   break;
			case '2': addMatrices(first, second);      break;
			case '3': multiplyMatrices(first, second); break;
			case '4': transpose(first); 		   break;
			case '5': cout<<"Thank you for using the Matrix Calculator!\n"; break;
			default:  cout<<endl<<"<- - * * Invalid Selection * * - ->\n";
		};
	}
	while(select != '5');   //exit loop when the user enters the number five
	
	
	return 0;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *Purpose:	    This funciotn determines if a matrix is*
 *	  	    symmetric and prints the results to the* 
 *	  	    screen.                                *
 *preconditions:    it requires that one matrix adt is     *
 *	            passed to it.                          *
 *postconditions:   it displays results to the monitor     *
 *	  	    it has no return values                *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void symmetric(matrix one)
{
	//this function assumes that the matrix is symmetric until proven false
	bool isSymmetric = true;

	
	//the dimensions of the matrix must be at least 2x2
	//and the matrix must be square
	if((one.rows == one.cols) && (one.rows > 1))
	{
		/*
		By setting i to the number of rows in the matrix  - 1 and 
		j to the number of cols in the matrix -2, this loop is able
		to traverse through the matrix and will skip the elements
		that make the main diaginal of the matrix.
		*/
		for(int i = (one.rows-1), j = (one.cols-2); j >= 0; i--, j--)
		{
			for(int k = 0; k <= j; k++)
			{
				if(one.arr[i][k] != one.arr[k][i])
				{
					isSymmetric = false;
					k = j + 1; // breaking out of the inner for loop
					j = -1;    // breaking out of the outter for loop					
				}// end if
			}// end k loop
		}// end ij loop

	}
	else
		isSymmetric = false;
		
	if(isSymmetric)
		cout<<endl<<"The matrix is symmetric\n";
	else
		cout<<endl<<"The matrix is not symmetric\n";
} // end symmetric(matrix)

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *Purpose:        This function add two matrices together and* 
 *                displays it to the user                    *
 *Preconditions:  it requires that two matrix adts are passed* 
 *	          to it.                                     *
 *Postconditions: it displays the results of the addition to *
 *                the monitor	                             *
 *		  it has no return values                    *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void addMatrices(matrix one, matrix two)
{
	if(one.rows == two.rows && one.cols == two.cols)
	{
		matrix outPut;
		
		//asigning dimensions to the matrix output
		outPut.rows = one.rows;
		outPut.cols = one.cols;
		
		cout<<"Here is the sum of the two matrices\n\n";
		
		//adding the two matrices together
		for(int i = 0; i < one.rows; i++)
		{
			for(int j = 0; j < one.cols; j++)
				outPut.arr[i][j] = one.arr[i][j] + two.arr[i][j];
		}
		
		//out put sum matrix to the user
		for(int i = 0; i < outPut.rows; i++)
		{
			for(int j = 0; j < outPut.cols; j++)
				cout<<setw(4)<<outPut.arr[i][j];
			cout<<endl;
		}
	}
	else
		cout<<"<- - * * Invalid Dimensions * * - ->\n";
}// end addMatrices(matrix, matrix)

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *Purpose:        This function multiplies two matrices      * 
 *                together and displays it to the user       *
 *Preconditions:  it requires that two matrix adts are passed* 
 *	          to it.                                     *
 *Postconditions: it displays the results of the product to  *
 *                the monitor	                             *
 *		  it has no return values                    *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void multiplyMatrices(matrix one, matrix two)
{
	if(one.cols == two.rows)
	{
		matrix outPut;
		
		//asigning dimensions
		outPut.rows = one.rows;
		outPut.cols = two.cols;
		
		/*
		computers n x p matrix one * two 
		for n x m matrix one, m x p matrix two
		and stores the results in outPut
		*/
		for(int i = 0; i < one.rows; i++)
		{
			for(int j = 0; j < two.cols; j++)
			{
				outPut.arr[i][j] = 0;
				
				for(int k = 0; k < one.cols; k++)
					outPut.arr[i][j] = (outPut.arr[i][j] + (one.arr[i][k] * two.arr[k][j]));
			}
		}
		
		cout<<"Here is the product of the two matrices\n\n";
		
		//out put product matrix to the user
		for(int i = 0; i < outPut.rows; i++)
		{
			for(int j = 0; j < outPut.cols; j++)
				cout<<setw(4)<<outPut.arr[i][j];
			cout<<endl;
		}		
	}
	else
		cout<<"<- - * * Invalid Dimensions * * - ->\n";
}// end multiplyMatrices(matrix, matrix)

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *Purpose:        This function transposes a matrix          * 
 *                and displays it to the user                *
 *Preconditions:  it requires that one matrix adt is passed  * 
 *	          to it.                                     *
 *Postconditions: it displays the results of the transpose   *
 *                to the monitor                             *
 *		  it has no return values                    *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void transpose(matrix one)
{
	for(int i = 0; i < one.cols; i++)
	{
		for(int j = 0; j < one.rows; j++)
		{
			cout<<setw(4)<<one.arr[j][i];
		}
		cout<<endl;
	}
}// end transpose(matrix)
