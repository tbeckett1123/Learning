# include <math.h>
# include <stdio.h>
# define PI 3.14159265358
# include "/usr/local/home/accts/tdb2q/csci4330/mpich2-1.0.5p3/mpich2i/include/mpi.h"

int main(int argc, char** argv)
{
	int rank, nProcs, i, sleep_time, sInterval, quit, dest, intervals;
	MPI_Status status;
	FILE* fp;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);


	sInterval = PI / (float)nProcs * (float)rank + PI / (float)nProcs / 2.0;

	intervals= sqrt(3.0 * pow(sin(sInterval/2.0), 3.0);

	if(rank == 0)
	{
		for( i = 1 ; i < nProcs; i++)
		{
			MPI_Recv(&sInterval, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status );
			intervals += sInterval;
		}
		
	}
			
	else
	{
		//send tha interval back to rank 0 //
		MPI_Send(&intervals, 1 MPI_INT, 0, 0, MPI_COMM_WORLD,
		
	}
	
	MPI_Finalize();
	
	return 0;
}
