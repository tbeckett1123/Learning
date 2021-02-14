/*
 * HWP/Conway BY student name, CSCI 3250-001, Due: mm/dd/yy
 * PROGRAM ID:  hwpconway.c / Problem using Unix semaphores
 * AUTHOR: Tim Beckett 
 * INSTALLATION:  MIDDLE TENNESSEE STATE UNIVERSITY
 *
 * REMARKS:  This program illustrates the use of shared memory segments
 * and System V-style semaphores.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>


/* --- Constants and Useful Definitions ----------------------------------- */
#define EODsentinel '#'
#define BLOCKMAX  10
#define LINEMAX   24
#define RDBUFSIZE  4
#define PRBUFSIZE  7

#define  SUCCESS 0
#define  FAILURE 1

/* Error message macros */
#define ERROR(msg) \
  ((void)fprintf(stderr,"ERROR \"%s\": %d> %s\n", \
  __FILE__,__LINE__, msg ) )
#define OS_ERROR(msg) \
  ((void)fprintf(stderr,"ERROR \"%s\": %d> ", __FILE__,__LINE__),\
  perror(msg) )


/* --- Global Variables, shared by main() and CleanupIPC() ---------------- */
int   eRD = -1;             /* Semaphore "eRD" ID (integer value)           */
int   nRD = -1;             /* Semaphore "nRD" ID (integer value)           */
int   ePR = -1;             /* Semaphore "ePR" ID (integer value)           */
int   nPR = -1;             /* Semaphore "nPR" ID (integer value)           */

int   pidReadInput   = -1;  /* ReadInput process id                         */
int   pidSquash      = -1;  /* Squash process id                            */
int   pidPrintOutput = -1;  /* PrintOutput process id                       */

int   shm_rdbuf = -1;       /* Shared memory buffer segment ID number       */
int   shm_prbuf = -1;       /* Shared memory buffer segment ID number       */



/* --- Functions ---------------------------------------------------------- */

void
CleanupIPC()
{
	/* Remove any active semaphores and return resources to OS */
	eRD != -1            ? semctl(eRD,    0, IPC_RMID, 0) : 0;
	nRD != -1            ? semctl(nRD,    0, IPC_RMID, 0) : 0;
	ePR != -1            ? semctl(ePR,    0, IPC_RMID, 0) : 0;
	nPR != -1            ? semctl(nPR,    0, IPC_RMID, 0) : 0;

	/* Remove any active shared memory segments and return resources to OS */
	shm_rdbuf != -1      ? shmctl(shm_rdbuf, IPC_RMID, 0) : 0;
	shm_prbuf != -1      ? shmctl(shm_prbuf, IPC_RMID, 0) : 0;

	/* Kill all children spawned by this process */
	pidReadInput   != -1 ? kill(pidReadInput,    SIGKILL) : 0;
	pidSquash      != -1 ? kill(pidSquash,       SIGKILL) : 0;
	pidPrintOutput != -1 ? kill(pidPrintOutput,  SIGKILL) : 0;
}

int
InitialSem(int InitialValue)
{
	int semid;
	union semun 
	{
		int              val;     /* for SETVAL */
		struct semid_ds  *buf;    /* for IPC_STAT and IPC_SET */
		ushort           *array;  /* FOR GETALL AND SETALL    */
	} arg;

	if ( (semid = semget(IPC_PRIVATE, 1, 0600)) == -1)
	{
		OS_ERROR("Unable to obtain a semaphore.");
		exit(FAILURE);
	}
	arg.val = InitialValue;
	if ( semctl(semid, 0, SETVAL, arg) == -1 )
	{
		OS_ERROR("Unable to initialize semaphore.");
		exit(FAILURE);
	}
	return semid;
}

int
Pwait(int semid)
{
	int retval;
	struct sembuf  p_buf;

	p_buf.sem_num = 0;
	p_buf.sem_op  = -1;
	p_buf.sem_flg = SEM_UNDO;

	while ( ((retval = semop(semid, &p_buf, 1)) == -1) && (errno==EINTR))
		;
	return retval;
}

int
Vsignal(int semid)
{
	int retval;
	struct sembuf  v_buf;

	v_buf.sem_num = 0;
	v_buf.sem_op  = 1;
	v_buf.sem_flg = SEM_UNDO;

	while ( ((retval = semop(semid, &v_buf, 1)) == -1) && (errno==EINTR))
		;
	return retval;
}







/* --- Main routine ------------------------------------------------------- */

int
main()
{
	int   waitReturn;         /* PID value                                 */
	int   returnStatus;       /* Return status value                       */


	/* --- Set-up and initialize semaphores. --- */
	eRD = InitialSem(RDBUFSIZE);
	nRD = InitialSem(0);
	ePR = InitialSem(PRBUFSIZE);
	nPR = InitialSem(0);


	/* --- Set-up shared memory. --- */
	shm_rdbuf = shmget(IPC_PRIVATE, RDBUFSIZE,   0600);
	shm_prbuf = shmget(IPC_PRIVATE, PRBUFSIZE,   0600);


	/* --- Start the "ReadInput" process. --- */
	if ( (pidReadInput = fork()) < 0)
	{
		OS_ERROR("Can't fork to run ReadInput process.");
		CleanupIPC();
		exit(errno);
	}

	/* Fork succeeded. */
	if (pidReadInput == 0)
	{   /* === Child process:  Act as "ReadInput" producer. === */
		char * rdbuf;          /* Buffer of characters to "Squash" */
    	char input;
    	int back, cnt;
    	/*
    	input is used for relaying  chars to the rdbuf array
    	back is used to keep track of the next element in the
    	rdbuf array that is to be written to.
    	*/
		/* Connect shared memory segment (rdbuf) to this address space. */
		rdbuf = (char *) shmat(shm_rdbuf, NULL, 0);

    back = cnt = 0;
    
	do
    {
        input = getchar();
		getchar();

        cnt++;

        if(cnt < BLOCKMAX)  /*when cnt reacHes BLOCKMAX*/
        {                   /*insert a space*/
            Pwait(eRD);
            rdbuf[back] = input;
            Vsignal(nRD);
        }
        else
        {
            Pwait(eRD);
            rdbuf[back] = input;
            Vsignal(nRD);

            back = (back + 1) % RDBUFSIZE;

            Pwait(eRD);
            rdbuf[back] = ' ';
            Vsignal(nRD);

            cnt = 0;
        }

        back = (back + 1) % RDBUFSIZE;

    }while(input != EODsentinel);
  
	pause();   /* Sleep until killed. */
	
  }


	/* --- Start the "Squash" process --- */
	if ( (pidSquash = fork()) < 0)
	{
		OS_ERROR("Can't fork to run Squash process.");
		CleanupIPC();
		exit(errno);
	}

	/* Fork succeeded. */
	if (pidSquash == 0)
	{   /* === Child process:  Act as "Squash" consumer/producer. === */
		char * rdbuf;          /* Buffer of characters from "ReadInput" */
		char * prbuf;          /* Buffer of characters to "PrintOutput" */
		int    rdFront, prBack;    /* prbuf back subscript */
		char   buffer, sqbuffer; 

		/* Connect shared memory segment (rdbuf) to this address space. */
		/*                             (connect as READ-ONLY)           */
		rdbuf = (char *) shmat(shm_rdbuf, NULL, SHM_RDONLY);

		/* Connect shared memory segment (prbuf) to this address space. */
		prbuf = (char *) shmat(shm_prbuf, NULL, 0);

		rdFront = prBack = 0;

		do
		{
			Pwait(nRD);
			buffer = rdbuf[rdFront];
			Vsignal(eRD);

			rdFront = (rdFront + 1) % RDBUFSIZE;

			if(buffer == '*')
			{
				Pwait(nRD);
				sqbuffer = rdbuf[rdFront];
				Vsignal(eRD);

				rdFront = (rdFront + 1) % RDBUFSIZE;
				
				if(buffer == sqbuffer)
				{
					Pwait(ePR);
					prbuf[prBack] = '!';
					Vsignal(nPR);
					
					prBack = (prBack + 1) % PRBUFSIZE;
				}
				else
				{
					Pwait(ePR);
					prbuf[prBack] = buffer;
					Vsignal(nPR);

					prBack = (prBack + 1) % PRBUFSIZE;
					
					Pwait(ePR);
					prbuf[prBack] = sqbuffer;
					Vsignal(nPR);

					prBack = (prBack + 1) % PRBUFSIZE;
				}
			} 
			else
			{
				Pwait(ePR);
				prbuf[prBack] = buffer;
				Vsignal(nPR);

				prBack = (prBack + 1) % PRBUFSIZE;
			}
		}while(!((buffer == EODsentinel) || (sqbuffer == EODsentinel)));
		
        pause();   /* Sleep until killed. */
	}


	/* --- Start the "PrintOutput" process --- */
	if ( (pidPrintOutput = fork()) < 0)
	{
		OS_ERROR("Can't fork to run PrintOutput process.");
		CleanupIPC();
		exit(errno);
	}

	/* Fork succeeded. */
	if (pidPrintOutput == 0)
	{   /* === Child process:  Act as "PrintOutput" consumer. === */

		char * prbuf;          /* Buffer of characters from "Squash" */
		int cnt, front;
		char outPut;

		/* Connect shared memory segment (prbuf) to this address space. */
		/*                             (connect as READ-ONLY)           */
		prbuf = (char *)  shmat(shm_prbuf, NULL, SHM_RDONLY);

		front = cnt = 0;

		Pwait(nPR);
		outPut = prbuf[front];
		Vsignal(ePR);	

		front = (front + 1) % PRBUFSIZE;

		while(outPut != EODsentinel)
		{
			fprintf(stdout, "%c", outPut);

			cnt++;

			if(cnt == LINEMAX)
			{
				fprintf(stdout, "\n");

				cnt = 0;
			}

			Pwait(nPR);
			outPut = prbuf[front];
			Vsignal(ePR);

			front = (front + 1) % PRBUFSIZE;
				
		}
	
		fprintf(stdout, "\n");
		
		exit(SUCCESS);
	}


	/* === Parent process: Wait for "PrintOutput" process to finish === */
	while (pidPrintOutput != (waitReturn=wait(&returnStatus)))
		if ((waitReturn==-1) && (errno!=EINTR))
			break;

	/* Finalizations */
	CleanupIPC();

	exit(SUCCESS);
} /* end main */
