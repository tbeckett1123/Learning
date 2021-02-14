/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	Programmer:		Timothy Beckett													   *
 *	Date:			11/10/2006														   *
 *	Purpose:		This program will prompt for the number of variable and then the   *
 *					coefficients and right hand side of each equation in turn.  It     *
 *					will then use Gaussian elimination with partrial pivoting to the   *
 *                  system.  It will then display the solution or report the errors    *
 *					that occured.													   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

# include <iostream>
# include <iomanip>
# include <cmath>

using namespace std;

const int NBREQN = 20;		//MAX

void gauss(int N, float A[NBREQN][NBREQN+1], float result[NBREQN]);
// Solve system of N linear equations with N unknowns
// using Gaussian elimination with scaled partial pivoting
// Precondition:  N <= NBREQN
// First N rows and N+1 columns of A contain the system
// with right-hand sides of equations in column N+1
// original contents of A are destroyed
// solution returned in result array
// throw an exception with what = "Gauss method failed" if the process fails

int main()
{
	float	result[NBREQN],
			A[NBREQN][NBREQN+1];

	int		N, e;

	//intialize the arrays
	for(int i = 0; i < NBREQN; i++)
	{
		result[i] = 1;

		for(int j = 0; j < NBREQN + 1; j++)
			A[i][j]	= 1;
	}

	cout << right << setfill('-') 
		 << setw(43) << " How to enter a matrix " << setw(21) << "-\n"
		 << "If this is your system of equations:\n"
		 << "9x_1 + 8x_2 = 7\n"
		 << "6x_1 + 5x_2 = 4\n"
		 << "The matrix size is determined by the number of variables.\n"
		 << "The number of variables in this case is 2.\n"
		 << "The matrix will be 2x3.\n"		 
		 << "The system of equation would be entered into the matrix like this:\n"
		 << "9 8 7\n"
		 << "6 5 4\n"
		 << setw(65) << "-\n\n"
		 << setfill(' ');
		 
		

	cout << endl 
		 << endl
		 << "Enter the number of variables: "; cin >> N;

	//check for valid number N
	//the user gets three chances to correct for an invalid N
	for(e = 0; (N > NBREQN || N < 2) && e < 3; e++)
	{
		cerr  << "The sive you entred is invalid\n"
			  << "Please enter a number between 2 and 20: "; cin >> N;
		cerr  << endl
			  << endl;
	}

	if(e == 3)
	{
		cerr  << "You have failed to enter a valid number of veriables\n"
			  << "Shutting down ...\n";
		exit(1);
	}
	
	cout << endl 
		 << endl
		 << "Now enter each row of the matrix until all rows have been entered:\n"
		 << "You may use more than one line to enter a row if needed.\n";

	//get the matrix from the user
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N + 1; j++)
			cin >> A[i][j];

	try
	{
		gauss(N, A, result);

		cout << endl 
			 << endl
			 << "The results are:\n";
		
		for(int i = 0; i < N; i++)
			cout <<"x"<< i+1 <<" = "<< result[i] << endl;

		cout << endl
			 << endl;
	}
	catch(exception e)
	{
		cerr << "An error has occured\n" << e.what() << endl;
	}
	
	return 0;
}


// Solve system of N linear equations with N unknowns
// using Gaussian elimination with scaled partial pivoting
// Precondition:  N <= NBREQN
// First N rows and N+1 columns of A contain the system
// with right-hand sides of equations in column N+1
// original contents of A are destroyed
// solution returned in result array
// throw an exception with what = "Gauss method failed" if the process fails
void gauss(int N, float A[NBREQN][NBREQN+1], float result[NBREQN])
{
	int		*indx  = new int[N],		//Array containg a permuation of 1..N
			maxIndx;					

	float	*scale = new float[N],		//Array containg N scaling factors
			maxRatio,
			ratio,
			sum;					

	//initialze index array
	for(int i = 0; i < N; i++)
		indx[i] = i;
	
	//determine scale factors
	for(int row = 0; row < N; row++)
	{
		scale[row] = fabs(A[row][0]);

		for(int col = 1; col < N; col++)
		{
			if(fabs(A[row][col]) > scale[row])
				scale[row] = fabs(A[row][col]);
		}
	}

	//start forward elimination
	for(int k = 0; k < N; k++)
	{
		//determine index of pivot row
		maxRatio = fabs(A[ indx[k] ][k] / scale[ indx[k] ]);

		maxIndx = k;

		for(int i = k + 1; i < N; i++)
		{
			if( fabs( A[ indx[i] ][k] ) / scale[ indx[i] ] > maxRatio )
			{
				try
				{
					maxRatio = fabs( A[ indx[i] ][k] ) / scale[ indx[i] ];
				}
				catch(exception &e)
				{
					//clean up dynamic memory
					delete[] indx;
					delete[] scale;

					throw( exception( e.what() ) );
				}				

				maxIndx = i;
			}
		}

		if(maxRatio == 0)
		{
			//no pivot available if maxRatio is zero

			//clean up dynamic memory
			delete[] indx;
			delete[] scale;
			
			throw exception("NO PIVOT AVAIABLE\n");
		}
		std::swap<int>(indx[k], indx[maxIndx]);
		
		for(int i = k + 1; i < N; i++)
		{
			try
			{
				ratio = -1 * A[ indx[i] ][k] / A[ indx[k] ][k];
			}
			catch(exception &e)
			{
				//clean up dynamic memory
				delete[] indx;
				delete[] scale;
				
				throw( exception( e.what() ) );
			}

			for(int col = k; col < N + 1; col++)
				A[ indx[i] ][col] += ratio * A[ indx[k] ][col];
		}
	}

	//This is needed to get rid of weird small numbers
	//that are close to zero when it in fact should be zero.
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N + 1; j++)
			A[i][j] = (fabs( A[i][j] ) > 1.0e-007) ? A[i][j] : 0;

	//check to see if a solution exist	

	for(int i = 0; i < N; i++)
	{
		sum = 0;

		for(int j = 0; j < N; j++)		
			sum += A[i][j];

		if(!sum)
		{
			//clean up dynamic memory
			delete[] indx;
			delete[] scale;

			throw( exception("No Solution or Infinite Solutions") );
		}
	}

	//back substitution

	for(int k = N - 1; k > -1; k--)
	{
		sum = 0;

		for(int col = k + 1; col < N; col++)
			sum += A[ indx[k] ][col] * A[ indx[col] ][N];

		try
		{
			A[ indx[k] ][N] = ( A[ indx[k] ][N] - sum ) / A[ indx[k] ][k];			
		}
		catch(exception &e)
		{
			//clean up dynamic memory
			delete[] indx;
			delete[] scale;

			throw( exception( e.what() ) );
		}
	}

	//copy solution in correct order to result array
	for(int k = 0; k < N; k++)
		result[k] = A[ indx[k] ][N];

	//clean up dynamic memory
	delete[] indx;
	delete[] scale;
}//end of gauss