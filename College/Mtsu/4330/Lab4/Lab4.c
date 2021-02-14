/* Programmer:		Timothy Beckett
 * Class:		CSCI 4330
 * Instructor:		Dr. Pettey
 * Description:		This program uses trapezoidal
 * 			integration to approximate the
 * 			function f(x).  f(x) is defined
 * 			as the square root of three 
 * 			times the the cude of the sine
 * 			of x divided by 2.  There are
 * 			no inputs; the range is assumed
 * 			to be from zero to Pie.
 * 			The more processes you run the 
 * 			more subdivisions into trapazoids
 * 			there will be, thus the more
 * 			accurate the approximation will
 * 			be.
 * Note:		This program must be compiled
 * 			with the mpicc -lm
 * * * * * * * * * * * * * * * * * * * * * * * * * * */

# include <stdio.h>
# include "/usr/local/home/accts/tdb2q/csci4330/mpich2-1.0.5p3/mpich2i/include/mpi.h"
# include <math.h>
# define PI 3.14159265
# define a 0.0   /* lower bound of integral */
# define b PI    /* upper bound of integral */

char fx[] = "(3sin^3(x/2))^(1/2)"; /* place a string represenation of f here*/

double f(double x)
{
	float sinxdiv2 = sin(x/2.0);
	
	return sqrt(3.0 * sinxdiv2 * sinxdiv2 * sinxdiv2);
}

int main(int argc, char** argv)
{
	int rank, nProcs;

	double slice, h, sum, integral;
	
	MPI_Init(&argc, &argv);			/*setup mpi stuff*/
	
	MPI_Comm_size(MPI_COMM_WORLD, &nProcs);
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	h = (b - a) / (double)nProcs; /* calculate the mid point */

	/*
	 * the integral of f(x) on the interval a to b is
	 * h / 2 * ( f(a) + 2 * f(x1) + 2 * f(x2) + ... + 2 * f(xn-1) + f(b) )
	 * 
	 * xk is defined as k * h where k = 1 to n-1
	 * 
	 * */
	if(rank == 0)
	{	
		slice = f(a) + 2.0 * f(h); /* sum the lower bound and x1 */
		
		/* MPI_Reduce is performing the sumation of the intervals, and
		 * process zero get the sumation; this is a all-to-one reduce.
		 * 
		 * the sum of the slices is placed in sum.
		 */
		MPI_Reduce(&slice, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		integral = h * 0.5 * sum;

		printf("The integral for %s on a interval of %0.5lf to %0.5lf is %0.5lf\n", fx, a, b, integral);
	}
	else if(rank == nProcs - 1)
	{
		slice = f(b); /* sum the upper bound */
		
		MPI_Reduce(&slice, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);		
	}
	else
	{
				/* adding one to rank to account for the difference of
				 * zero indexing of the processes and one indexing of
				 * the trapizoidal formula; rank = k - 1 
				 */
		slice = 2.0 * f((rank + 1) * h); /* sum x2 through xn-1 */
		
		MPI_Reduce(&slice, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);		
	}
	
	MPI_Finalize(); 
	
	return 0;
}
