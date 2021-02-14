/* Sample thread program to add the numbers in an array */
/* Adapted from Parallel Programming by Barry Wilkinson and Michael Allen
 * Prentice Hall 1999 pp254 - 255
 * All lines involving mutex 2 were added by Chrisila Pettey
 */

#include <stdio.h>
#include <pthread.h>
#define array_size 1000
#define no_processes 10
			/*shared data*/
int a[array_size];	/*array of numbers to sum*/
int global_index = 0;	/*global index */
int sum = 0;		/*final result, also used by slaves*/
pthread_mutex_t mutex1;	/*mutually exclusive lock variable */
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER; /*additional mutex*/

void *slave(void *ignored)	/*slave threads*/
{
	int local_index, partial_sum = 0;
	do{
		pthread_mutex_lock(&mutex1);	/*get next index into the array*/
			local_index = global_index;	/*get current index*/
			global_index++;			/*increment global index*/
		pthread_mutex_unlock(&mutex1);
		if(local_index < array_size)
			partial_sum += *(a + local_index);
	} while (local_index < array_size);

	pthread_mutex_lock(&mutex2);		/*add partial sum to global sum*/
		sum += partial_sum;
	pthread_mutex_unlock(&mutex2);

	return;			/*thread exits */
}

main()
{
	int i;
	pthread_t thread[10];			/*threads*/
	pthread_mutex_init(&mutex1,NULL);	/*initialize mutex*/

	for(i=0;i<array_size;i++)		/*initialize a*/
		a[i] = i+1;

	for(i=0;i<no_processes;i++)		/*create threads */
		if(pthread_create(&thread[i],NULL,slave,NULL) != 0)
			perror("Pthread_create fails");

	for(i=0;i<no_processes; i++)		/*join threads*/
		if (pthread_join(thread[i],NULL) != 0)
			perror("Pthread_join fails");

	printf("The sum of 1 to %i is %d\n",array_size,sum);
}/*end main*/
