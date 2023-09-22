/*
 * CSCI3240: Project 4
 *
 * Timothy Beckett tdb2q
 *
 * Project4.c - Source file with your solutions to the Lab.
 *          This is the file you will submit in the D2L -> Project3 dropbox.
 *
 *   Make sure you have insightful comments in your code. 
 *
 */
#include "csapp.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define ADD_RECORD       1
#define SEARCH_NAME      2
#define SEARCH_ZIP_CODE  3
#define SEARCH_SALARY    4
#define EXIT_APPLICATION 5

#define BUFFER_SIZE        258
#define FIELD_SIZE         128
#define LINE_SIZE          1024
#define COLUMN_BUFFER_SIZE 15

#define GT 1
#define LT 2
#define EQ 3
#define GTE 4
#define LTE 5

sem_t empty_writer;
sem_t full_writer;
pthread_mutex_t mutex_writer;

sem_t empty_collector;
sem_t full_collector;
pthread_mutex_t mutex_collector;

struct Parameters
{
    char *ClientHostname;
    char *ClientPort;
    int Connfd;
};

struct Struct_Employee_Info
{
    char FirstName[FIELD_SIZE];
    char LastName[FIELD_SIZE];
    char Department[FIELD_SIZE];
    int   ZipCode;
    double Salary;
    struct Struct_Employee_Info *Next;
} *Employees;

// Structure way of tracking dynamic memory to free before ending program
struct Garbage
{
    void *Unit;
    struct Garbage *Next;
} *Head = NULL;
void AddToThreadFinalizeList(struct Garbage *threadPtr, void *unit);
void Finalize(struct Garbage *head);

void* ServerFunction(void* args);
int LineCount(FILE *fptr);
void LoadDatabase(struct Garbage *threadPtr, char *filename, struct Struct_Employee_Info **employees);
char* SearchName(struct Garbage *threadPtr, struct Struct_Employee_Info *employees, char *firstName, char *lastName);
char* SearchZipCode(struct Garbage *threadPtr, struct Struct_Employee_Info *employees, int zipCode);
char* SearchSalary(struct Garbage *threadPtr, struct Struct_Employee_Info *employees, double Salary, int compType);
void FormattedRow(struct Garbage *threadPtr, struct Struct_Employee_Info *record, char* buffer, int *index);
char* FormattedValue(char *value);
void AddCommas(struct Garbage *threadPtr, char* str);
void AddRecord(int connfd, char* buffer);

int main(int argc, char **argv)
{
    sem_init(&empty_writer, 0, 1); // setting up thread magement
    sem_init(&full_writer, 0, 0);
    pthread_mutex_init(&mutex_writer, NULL);

    sem_init(&empty_collector, 0, 1); // setting up thread magement
    sem_init(&full_collector, 0, 0);
    pthread_mutex_init(&mutex_collector, NULL);

	int listenfd;
	int connfd; //file descriptor to communicate with the client
	socklen_t clientlen;
	struct sockaddr_storage clientaddr; /* Enough space for any address */

	char client_hostname[MAXLINE], client_port[MAXLINE];
	if (argc != 2)
	{
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(0);
	}

	listenfd = Open_listenfd(argv[1]);

	//Server runs in the infinite loop.
	//To stop the server process, it needs to be killed using the Ctrl+C key.
	while (1)
	{
		clientlen = sizeof(struct sockaddr_storage);

		// wait for the connection from the client.
		connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen); Getnameinfo((SA *) &clientaddr, clientlen, client_hostname, MAXLINE,client_port, MAXLINE, 0);

		printf("Connected to (%s, %s)\n", client_hostname, client_port);

		//function to interact with the client
        struct Parameters *params = (struct Parameters*)malloc(sizeof(struct Parameters));
        params->ClientHostname = client_hostname;
        params->ClientPort = client_port;
        params->Connfd = connfd;

        pthread_t t;

        pthread_create(&t, NULL, ServerFunction, (void*)params);
	}

    sem_destroy(&empty_writer); // cleaning up thread management
    sem_destroy(&full_writer);
    pthread_mutex_destroy(&mutex_writer);
    sem_destroy(&empty_collector);
    sem_destroy(&full_collector);
    pthread_mutex_destroy(&mutex_collector);

	exit(0);
}

// Listener function
void* ServerFunction(void *args)
{
    struct Garbage *threadPtr, *employeesTracker;
    struct Parameters *params = (struct Parameters*)args;

    AddToThreadFinalizeList(threadPtr, params);

	char buffer[MAXLINE], //MAXLINE = 8192 defined in csapp.h
         successMessage[MAXLINE] = "I got your message\n",
         *response = NULL,
         firstName[FIELD_SIZE],
         lastName[FIELD_SIZE];
	size_t n;
    int selection, zipCode, compType;
    double salary;

    //resetting the buffer
	bzero(buffer,MAXLINE);

	n = read(params->Connfd, buffer, MAXLINE);

	printf("server received %ld bytes message\n", n);
	printf("Message from Client: %s\n",buffer);

	write(params->Connfd,successMessage,strlen(successMessage));

    // assign the string parts from request
    sscanf(buffer, "%d,%[^,],%[^,],%d,%lf,%d", &selection, firstName, lastName, &zipCode, &salary, &compType);

    LoadDatabase(employeesTracker, "records.csv", &Employees);  // 1 time setup for database.

    switch (selection)
    {
        case ADD_RECORD:
            AddRecord(params->Connfd, buffer);
            break;
        case SEARCH_NAME:
            response = SearchName(threadPtr, Employees, firstName, lastName);

            bzero(buffer, MAXLINE); // send response buffer size
            strncpy(buffer, response, strlen(response));

            write(params->Connfd, buffer, MAXLINE); // send reponse to client

            break;
        case SEARCH_ZIP_CODE:
            response = SearchZipCode(threadPtr, Employees, zipCode);

            bzero(buffer, MAXLINE); // send response buffer size
            strncpy(buffer, response, strlen(response));

            write(params->Connfd, buffer, MAXLINE); // send reponse to client

            break;
        case SEARCH_SALARY:
            response = SearchSalary(threadPtr, Employees, salary, compType);

            bzero(buffer, MAXLINE); // send response buffer size
            strncpy(buffer, response, strlen(response));

            write(params->Connfd, buffer, MAXLINE); // send reponse to client

            break;
    }

    Close(params->Connfd);

    printf("(%s, %s) disconnected\n", params->ClientHostname, params->ClientPort);

    Finalize(employeesTracker); // free dynamic memoory for the employee database
    Finalize(threadPtr);


    return NULL;
}

// Add Garbarge to clean
// Only use the Add functions for the list in question
void AddToThreadFinalizeList(struct Garbage *threadPtr, void *unit)
{
    // lock resources
    sem_post(&full_collector); // increment full slots (V function)
    pthread_mutex_lock(&mutex_collector); // wait for thread resources
    sem_wait(&empty_collector); // decrement empty slots (P function)

    if (threadPtr == NULL) // 1 time setup of garbage collection
    {
        threadPtr = (struct Garbage*)malloc(sizeof(struct Garbage));
        threadPtr->Unit = NULL;
        threadPtr->Next = NULL;
    }

    struct Garbage *New = (struct Garbage*)malloc(sizeof(struct Garbage));
    New->Unit = unit;
    New->Next = NULL;
    threadPtr->Next = New;


    // release resources
    pthread_mutex_unlock(&mutex_collector); // release thread resources
    sem_post(&empty_collector); // increment empty slots (V function)
}

// Free up dynamically created memory
void Finalize(struct Garbage *head)
{
    struct Garbage *current = head; // setup for freeing loop. node
    while(current != NULL)          // free up each item in the list 
    {
        struct Garbage *temp = current; // prep item to be freeed
        current = current->Next;        // advance the current pointer
        free(temp->Unit);               // free up the item
        free(temp);                     // free up the container
    }
}

// Counts the lines in the file
// It assumes the file is open, and will count the number of lines read from the position
// the position of the supplied file pointer will not be affected.
int LineCount(FILE *fptr)
{
    int count = 0;
    long pos = ftell(fptr); // get file current position
    char input;

    // count the number of lines
    while(fscanf(fptr, "%c", &input) != EOF)
        if (input == '\n')
            count++;

    // the line count is zero if the file is empty.
    // adding for for the last/first line.
    if (pos != ftell(fptr))
        count++;

    // reset the pointer back to its original position
    fseek(fptr, pos, SEEK_SET); 

    return count;
}

// loads the student records into a linked list of Struct_Employee_Info type
void LoadDatabase(struct Garbage * threadPtr, char *filename, struct Struct_Employee_Info **employees)
{
    FILE *fptr = fopen(filename, "r");
    char line[LINE_SIZE];

    *employees = NULL; // init the list of employees

    if (LineCount(fptr) == 0) // if the file is empty, you're done.  cheers!
    {
        fclose(fptr);
        return;
    }

    bzero(line, LINE_SIZE); // init the line buffer.

    while (fgets(line, LINE_SIZE, fptr) != NULL) // reading the line.
    {
        // create a new employee record
        struct Struct_Employee_Info *employee = (struct Struct_Employee_Info*)malloc(sizeof(struct Struct_Employee_Info));

        // init employee record
        // assign the string parts to employee properties. elements to the respective properties
        sscanf(line, "%[^,],%[^,],%d,%[^,],%lf", employee->FirstName, employee->LastName, &employee->ZipCode,  employee->Department, &employee->Salary);

        employee->Next = *employees;  // advance the list pointer
        *employees = employee;        // set the head of the list to the new student
                                      // set garbage collector to employee database
        AddToThreadFinalizeList(threadPtr, employee);  // add employee record to tracked garbage collection
                                     // record employees head pointer

        bzero(line, LINE_SIZE); // reset the line buffer
    }

    fclose(fptr);
}

// Search for records matching the first and last names
// returns a formatted string of the matches seperated by newlines
char* SearchName(struct Garbage *threadPtr, struct Struct_Employee_Info *employees, char *firstName, char *lastName)
{
    struct Struct_Employee_Info *current = employees;
    char* matches = NULL;
    int count = 0, i = 0, tSize;

    // find the number of matches
    while (current != NULL) 
    {
        if (strcmp(firstName, current->FirstName) == 0 && strcmp(lastName, current->LastName) == 0)
            count++;

        current = current->Next;
    }

    if (count != 0)
    {
        tSize = sizeof(char) * (count * 66) + 1;    // Calculate the size of the matches size
        matches = (char*)malloc(tSize);             // 65 is the length of the formatted row
                                                    // plu1 1 character for a newline and
                                                    // 1 character for the NULL termerator
        AddToThreadFinalizeList(threadPtr, matches);// Add matching records string to tracked garbage collection


        //clear the buffer
        bzero(matches, tSize);

        // find the matching records and create a formatted string with the results.
        current = employees;
        while (current != NULL)
        {
            if (strcmp(firstName, current->FirstName) == 0 && strcmp(lastName, current->LastName) == 0)
            {
                FormattedRow(threadPtr, current, matches, &i);
            }

            current = current->Next;
        }

        matches[i+1] = '\0'; // null terminate result string.
    }
    else
    {
        matches = (char*)malloc(25);
        AddToThreadFinalizeList(threadPtr, matches);
        strcpy(matches, "Record not found!\n");
    }

    return matches;
}

// Search for records matching the zip code
// returns a formatted string of the matches seperated by newlines
char* SearchZipCode(struct Garbage *threadPtr, struct Struct_Employee_Info *employees, int zipCode)
{
    struct Struct_Employee_Info *current = employees;
    char* matches = NULL;
    int count = 0, i = 0, tSize;

    // find the number of matches
    while (current != NULL) 
    {
        if (zipCode == current->ZipCode)
            count++;

        current = current->Next;
    }

    if (count != 0)
    {
        tSize = sizeof(char) * (count * 66) + 1;  // Calculate the size of the matches size
        matches = (char*)malloc(tSize);           // 65 is the length of the formatted row
                                                  // plu1 1 character for a newline and
                                                  // 1 character for the NULL termerator
        AddToThreadFinalizeList(threadPtr, matches); // Add matching records string to tracked garbage collection

        //clear the buffer
        bzero(matches, tSize);

        // find the matching records and create a formatted string with the results.
        current = employees;
        while (current != NULL)
        {
            if (zipCode == current->ZipCode)
                FormattedRow(threadPtr, current, matches, &i);

            current = current->Next;
        }

        matches[i+1] = '\0'; // null terminate result string.
    }
    else
    {
        matches = (char*)malloc(25);
        AddToThreadFinalizeList(threadPtr, matches);
        strcpy(matches, "Record not found!\n");
    }

    return matches;
}

// Search for records matching the salary
// returns a formatted string of the matches seperated by newlines
char* SearchSalary(struct Garbage *threadPtr, struct Struct_Employee_Info *employees, double salary, int compType)
{
    struct Struct_Employee_Info *current = employees;
    char* matches = NULL;
    int count = 0, i = 0, tSize;
    int iSalary = (int)(100.0 * salary); // shift the 10-1 and 10-2 places left and cast to int to trucate odd fractional values.
    // find the number of matches
    while (current != NULL) 
    {
        switch (compType)
        {
            case GT:
                if ((int)(100.0 * current->Salary) > iSalary)
                    count++;
                break;
            case LT:
                if ((int)(100.0 * current->Salary) < iSalary)
                    count++;
                break;
            case EQ:
                if (iSalary == (int)(100.0 * current->Salary))
                    count++;
                break;
            case GTE:
                if ((int)(100.0 * current->Salary) >= iSalary)
                    count++;
                break;
            case LTE:
                if ((int)(100.0 * current->Salary) <= iSalary)
                    count++;
                break;
        }
        current = current->Next;
    }

    if (count != 0)
    {
        tSize = sizeof(char) * (count * 66) + 1;  // Calculate the size of the matches size
        matches = (char*)malloc(tSize);           // 65 is the length of the formatted row
                                                  // plu1 1 character for a newline and
                                                  // 1 character for the NULL termerator
        AddToThreadFinalizeList(threadPtr, matches);        // Add matching records string to tracked garbage collection

        //clear the buffer
        bzero(matches, tSize);

        // find the matching records and create a formatted string with the results.
        current = employees;
        while (current != NULL)
        {
            switch (compType)
            {
                case GT:
                    if ((int)(100.0 * current->Salary) > iSalary)
                        FormattedRow(threadPtr, current, matches, &i);
                    break;
                case LT:
                    if ((int)(100.0 * current->Salary) < iSalary)
                        FormattedRow(threadPtr, current, matches, &i);
                    break;
                case EQ:
                    if (iSalary == (int)(100.0 * current->Salary))
                        FormattedRow(threadPtr, current, matches, &i);
                    break;
                case GTE:
                    if ((int)(100.0 * current->Salary) >= iSalary)
                        FormattedRow(threadPtr, current, matches, &i);
                    break;
                case LTE:
                    if ((int)(100.0 * current->Salary) <= iSalary)
                        FormattedRow(threadPtr, current, matches, &i);
                    break;
            }

            current = current->Next;
        }

        matches[i+1] = '\0'; // null terminate result string.
    }
    else
    {
       matches = (char*)malloc(25);
       AddToThreadFinalizeList(threadPtr, matches);
       strcpy(matches, "Record not found!\n");
    }

    return matches;
}

// Concatinates a formatted employee record string the the string buffer.
char nameBuffer[FIELD_SIZE * 2 + 1];
char salaryBuffer[10];
void FormattedRow(struct Garbage *threadPtr, struct Struct_Employee_Info *record, char* buffer, int *index)
{
    // setup name
    // clear the buffer
    bzero(nameBuffer, FIELD_SIZE * 2 + 1);
    strcat(nameBuffer, record->FirstName);
    strcat(nameBuffer, " ");
    strcat(nameBuffer, record->LastName);
    *(nameBuffer + strlen(record->FirstName) + strlen(record->LastName) + 2) = '\0';

    // add formatted name to the results record. the space is for column formatting
    *index += sprintf(buffer + *index, "%-15s ", FormattedValue(nameBuffer));
    *index += sprintf(buffer + *index, "%-15s ", FormattedValue(record->Department));
    *index += sprintf(buffer + *index, "%-15d ", record->ZipCode);

    //Convert salary to string and add commas
    bzero(nameBuffer, 10);  
    sprintf(salaryBuffer, "%-6.2lf", record->Salary);
    AddCommas(threadPtr, salaryBuffer);

    *index += sprintf(buffer + *index, "$%-s\n", FormattedValue(salaryBuffer));

}

// printing a substring of the value for tabular data.
char buffer[COLUMN_BUFFER_SIZE]; // I needed a buffer that would allow me to return a substring
char* FormattedValue(char *value)
{

    int sLength = strlen(value);

    // if the value is less within the column length return.
    if (sLength <= COLUMN_BUFFER_SIZE) 
        return value;

    // setup formatted name
    //clear the buffer
    bzero(buffer, COLUMN_BUFFER_SIZE);

    // the 3 dots indicates the value has been trucated for column
    strncpy(buffer, value, COLUMN_BUFFER_SIZE - 4);
    strcat(buffer, "...");

    return buffer;
}

//Format the decimal number with commas.
void AddCommas(struct Garbage *threadPtr, char *str)
{
    int len = strlen(str);
    int commaCount = (len - 1) / 3;     // Calculate the number of commas needed
    int newLen = len + commaCount;      // Calculate the new length of the string
    char* newStr = malloc(newLen + 1);  // Allocate memory for the modified string
    AddToThreadFinalizeList(threadPtr, newStr);
    int j = 0;

    // Iterate over the original string in reverse order
    for (int i = len - 1; i >= 0; i--) {
        newStr[j++] = str[i];  // Copy each character to the new string

        // Add a comma after every third digit, except for the first digit
        if (i > 0 && (len - i) % 3 == 0 && str[i] != '.')
            newStr[j++] = ',';
    }

    // Copy the modified string back to the original string buffer, reversing the order
    for (int i = 0; i < j; i++)
        str[i] = newStr[j - i - 1];

    str[j] = '\0';                    // Null terminate the modified string
}

void AddRecord(int connfd, char* buffer)
{
    // lock resources
    sem_post(&full_writer); // increment full slots (V function)
    pthread_mutex_lock(&mutex_writer); // wait for thread resources
    sem_wait(&empty_writer); // decrement empty slots (P function)

    char firstName[FIELD_SIZE];
    char lastName[FIELD_SIZE];
    char department[FIELD_SIZE];
    char zipCode[FIELD_SIZE];
    char salary[FIELD_SIZE];
    char buffer2[MAXLINE];
    int selection;

    // assign the string parts from request
    sscanf(buffer, "%d,%[^,],%[^,],%[^,],%[^,],%s", &selection, firstName, lastName, zipCode, department, salary);

    FILE *fptr = fopen("records.csv", "a+");

    if (fptr == NULL) // check file opened
    {
        printf("Failed to open the file.\n");
        return;
    }

    // append to the end of the file
    fprintf(fptr, "\n%s,%s,%s,%s,%s", firstName, lastName, zipCode, department, salary);

    fclose(fptr);

    bzero(buffer2, MAXLINE);
    strcpy(buffer2, "Record added Sucessfully!!\n");
    write(connfd, buffer2, MAXLINE); // send reponse to client

    // release resources
    pthread_mutex_unlock(&mutex_writer); // release thread resources
    sem_post(&empty_writer); // increment empty slots (V function)
}