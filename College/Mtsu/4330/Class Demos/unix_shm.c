/*Example program of two unix heavyweight processes adding the
 * numbers from 1 to 1000.  Copied from pp251 - 253 in
 * Parallel Programming, by Barry Wilkinson and Michael Allen,
 * Prentice Hall 1999
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <errno.h>
#define array_size 1000		/*no of elements in shared memory */
extern char *shmat();
void P(int *s);
void V(int *s);

int main()
{
	int shmid, s, pid;	/*shared memory, semaphore, proc id */
	char *shm;		/*shared mem. adr returned by shmat()*/
	int *a, *addr, *sum;	/*shared data variables*/
	int partial_sum;	/*partial sum of each process*/
	int i;

				/*initialize semaphore set*/
	int init_sem_value = 1;
	s = semget(IPC_PRIVATE, 1, (0600 | IPC_CREAT));
	if(s == -1)		/*if unsuccessful*/
	{
		perror("semget");
		exit(1);
	}
	if(semctl(s, 0, SETVAL, init_sem_value) < 0)
	{
		perror("semctl");
		exit(1);
	}

				/*create shared segment*/
	shmid = shmget(IPC_PRIVATE, (array_size*sizeof(int)+1),(IPC_CREAT|0600));
	if (shmid == -1)
	{
		perror("shmget");
		exit(1);
	}

				/*map segment to process data space*/
	shm = shmat(shmid, NULL, 0);
				/*returns address as a character*/
	if(shm == (char*)-1)
	{
		perror("shmat");
		exit(1);
	}

	addr = (int*)shm;	/*starting address */
	sum = addr;		/*accumulating sum */
	addr++;
	a = addr;		/*array of numbers, a[]*/

	*sum = 0;
	for(i=0;i<array_size;i++)	/*load array with numbers*/
		*(a+i) = i+1;

	pid = fork();		/*create child process */
	if(pid == 0)
	{
		partial_sum = 0;
		for(i=0;i<array_size;i=i+2)	/*child does every other */
			partial_sum += *(a + i);
	}
	else
	{
		partial_sum = 0;
		for(i=1;i<array_size; i=i+2)
			partial_sum += *(a + i);
	}

	P(&s);
		*sum += partial_sum;
	V(&s);

	printf("\nprocess pid = %d, partial sum = %d\n",pid,partial_sum);
	if(pid==0) exit(0); else wait(0);	/*terminate child*/
	printf("\nThe sum of 1 to %d is %d\n", array_size, *sum);

	if (semctl(s, 0, IPC_RMID, 1) == -1) /*remove semaphore*/
	{
		perror("semctl");
		exit(1);
	}
	if (shmctl(shmid, IPC_RMID, NULL) == -1) /*remove shared memory*/
	{
		perror("shmctl");
		exit(1);
	}
	return(0);
}/*end main*/

void P(int *s)
{
	struct sembuf sembuffer, *sops;
	sops = &sembuffer;
	sops->sem_num = 0;
	sops->sem_op = -1;
	sops->sem_flg = 0;
	if (semop(*s, sops, 1) < 0)
	{
		perror("semop");
		exit(1);
	}
	return;
}
void V(int *s)
{
	struct sembuf sembuffer, *sops;
	sops = &sembuffer;
	sops->sem_num = 0;
	sops->sem_op = 1;
	sops->sem_flg = 0;
	if (semop(*s, sops, 1) < 0)
	{
		perror("semop");
		exit(1);
	}
	return;
}
