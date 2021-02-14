/* *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 * Programmer:		Timothy Beckett			       * 
 * Class:		CSCI 4330			       * 
 * Instructor:		Dr. Pettey			       * 
 * Date Due:		02-07-07 			       * 
 * Destriction:		The objective of this program is to    * 
 * 			simulate a online game server.  This   * 
 * 			server will run ten players.  The      * 
 * 			game play will be simulated by prin-   * 
 * 			ting the player number, which will     * 
 * 			be issued by the server, the play      * 
 * 			lenght, and sleeping the requested     * 
 * 			number of seconds. 	               * 
 * Inputs:		The input will be expected to come     * 
 * 			from the keyboard or from file redi-   * 
 * 			rect at the console.  The expected     * 
 * 			inputs will be ten integers which      * 
 * 			will be the desired sleep/play time.   *
 * *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  */

# include <stdio.h>
# include <pthread.h>
# define MAX_THREAD 3
# define MAX_PLAYERS 10

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;


int finished[MAX_THREAD] = { 1, 1, 1 };


/* *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *   *
 * This method is designed to run in parallel with other processes like its self. * 
 * The thread id ptr should contain a value between 0 and THREAD_MAX.  That is it *
 * should contain a int pointer which will containthat value range. This value    *
 * will be used to identify the process running as well as index for setting the  *
 * finished flag.  								  * 
 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  */
void * player_thread(void * thread_id_ptr)
{
	int thread_id = *((int*)thread_id_ptr), /*get the id from the ptr*/
	    sleep_time;

	pthread_mutex_lock(&lock1); /*get input from std in*/
	
		scanf("%d", &sleep_time);
	
	pthread_mutex_unlock(&lock1);	
		
	printf("pid: %d, play length: %d\n", thread_id, sleep_time);

	sleep(sleep_time);
 
	finished[thread_id] = 1; /*alert server that thread is finished*/

	pthread_exit(0);
}


int main()
{
	pthread_t id[MAX_THREAD];	   /*player thread id*/
	int	  index_arr[MAX_PLAYERS],  /*player thread id index*/
		  itr, itr2,		   /*intorator*/
		  index,		   /*index*/
		  count;		   /*thread counter*/
		  
	printf("Enter in the desired sleep times:\n");

	/*start spawning and terminating threads as needed*/
 
	/*set the initial values of index (the pid) and process count to zero*/

	for(itr = 0, index = 0, count = 0; itr < MAX_PLAYERS; itr++) /*loop until maxium number of players has been reached*/
	{
		while(count > MAX_THREAD - 1) /*wait for a thread to open up*/
		{
			for(itr2 = 0, index = 0; itr2 < MAX_THREAD; itr2++) /*itorate through thread id array*/
			{
				if(finished[itr2] == 1) /*check for and terminate a finished thread*/
				{
					pthread_join(id[itr2],NULL);	/*kill the finished process*/
					count--;			/*increase the available thread count
									  this will allow while loop to end*/
					index = itr2;			/*save available PID*/
					itr2 = MAX_THREAD;		/*exit inner loop*/
				}
			}
		}

		/*spawn new thread*/
		index_arr[itr] = index; /*set the element of the array of players, for the player in question,
					  to the process id that is assigned to handle his/her thread*/

		finished[index] = 0; /*set thread finished status to false*/
		
		pthread_create(&id[index], NULL, player_thread, (void *)&index_arr[itr]);
		
		count++;	/*decrease the available thread count*/
		
		index = (index + 1) % MAX_THREAD;
	}

	/*finializing: terminating all processes for program shutdown*/
	
	for(itr = 0; itr < MAX_THREAD; itr++)
		pthread_join(id[itr], NULL);
	
	return 0;
}
