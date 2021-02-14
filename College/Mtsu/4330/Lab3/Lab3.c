/* Programmer:		Timothy Beckett
 * Class:		CSCI 4330
 * Instructor:		Dr. Pettey
 * Description:		The purpose of this program
 * 			is to implement mpi in order
 * 			to simulate a game server.
 * 			There are 4 processes. One
 * 			is the game server; it 
 * 			reads the data from a file
 * 			"games.dat" and passes the
 * 			appropriate information to
 * 			the other 3 processes which
 * 			handle the players of the 
 * 			game.  The other 3 are 
 * 			clones.  They expect a number
 * 			to be passed from the game
 * 			server.  This number will
 * 			tell the process how long to
 * 			sleep.  sleeping represents
 * 			game play.
 * * * * * * * * * * * * * * * * * * * * * * * * * * */

# include <stdio.h>
# include "/usr/local/home/accts/tdb2q/csci4330/mpich2-1.0.5p3/mpich2i/include/mpi.h"

int main(int argc, char** argv)
{
	int rank, nProcs, sleep_time, quit, dest;
	MPI_Status status;
	FILE* fp;

	MPI_Init(&argc, &argv);			/*setup mpi stuff*/
	
	MPI_Comm_size(MPI_COMM_WORLD, &nProcs);
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if(rank == 0)
	{
		quit = 0;
	
		if(fp = fopen("games.dat","r"))		/*if file fails to open shutdown*/
		{
			fscanf(fp, "%d", &sleep_time);	/*get first character*/
			
			while(feof(fp) != 1)		/*if end of file shutdown*/
			{ 
				
				/*get process id*/
				MPI_Recv(&dest, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			
				/*send data to ready process*/
				MPI_Send(&sleep_time, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
			
				/*get next character*/
				fscanf(fp, "%d", &sleep_time);
			}
			
			quit = -1; /*shutdown all other processes*/
			
			for(dest = 1; dest < nProcs; ++dest)
				MPI_Send(&quit, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
			
			fclose(fp);
		}
		else
		{
			printf("The file failed to open\n");

			quit = -1; /*tell all processes to shutdown*/

			for(dest = 1; dest < nProcs; ++dest)
				MPI_Send(&quit, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
			
			return -1;
		}
			
	}
	else
	{
		do
		{
			MPI_Send(&rank, 1, MPI_INT, 0, 1, MPI_COMM_WORLD); /*tell process 0 current process is ready*/

			MPI_Recv(&sleep_time, 1,  MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status); /*get data from process 0*/

			if(sleep_time > -1) /*if sleep time is less than 0 skip*/
			{
				printf("%d is playing for %d seconds\n", rank, sleep_time);

				sleep(sleep_time);
			}
			
		}while(sleep_time > -1); /*shutdown if told to by process 0 other wise loop*/
	}
	
	MPI_Finalize(); 
	
	return 0;
}
