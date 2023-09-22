/*
 * CSCI3240: Project 3
 *
 * Timothy Beckett tdb2q
 *
 * Project3.c - Source file with your solutions to the Lab.
 *          This is the file you will submit in the D2L -> Project3 dropbox.
 *
 *   Make sure you have insightful comments in your code. 
 *
 */
#include "csapp.h"

#define ADD_RECORD       1
#define SEARCH_NAME      2
#define SEARCH_ZIP_CODE  3
#define SEARCH_SALARY    4
#define EXIT_APPLICATION 5

#define RESPONSE_BUFFER_SIZE_BYTES 5
#define FIELD_SIZE                 128
#define LINE_SIZE                  1024
#define COLUMN_BUFFER_SIZE         15

#define GT '1'
#define LT '2'
#define EQ '3'
#define GTE '4'
#define LTE '5'

// Structure way of tracking dynamic memory to free before ending program
struct Garbage
{
    void *Unit;
    struct Garbage *Next;
} *Head = NULL;
void AddToFinalizeList(void *unit);
void Finalize();

void SearchName(int clientfd);
void SearchZipCode(int clientfd);
void SearchSalary(int clientfd);
void AddRecord(int clientfd);

int main(int argc, char *argv[])
{
    char *menu = "(1) Add record\n(2) Search by Name\n(3) Search by Zip Code\n(4) Search by Salary\n(5) Terminate\nSelect an option [1,2,3,4 or 5]:";

	int clientfd, //file descriptor to communicate with the server
        selection;
	char *host, *port;
	size_t n;

	if (argc != 3)
	{
		fprintf(stderr, "The host and port are required i.e. %s <host> <port>\n", argv[0]);
		exit(0);
	}

	host = argv[1];
	port = argv[2];

    do
    {
        clientfd = Open_clientfd(host, port);

        // prompt the user and execute the selection action
        printf("%s", menu);
        scanf("%d", &selection);

        switch (selection)
        {
            case ADD_RECORD:
                AddRecord(clientfd);
                break;
            case SEARCH_NAME:
                SearchName(clientfd);
                break;
            case SEARCH_ZIP_CODE:
                SearchZipCode(clientfd);
                break;
            case SEARCH_SALARY:
                SearchSalary(clientfd);
                break;
            case EXIT_APPLICATION:
                // valid input but no action to take inside do/while loop
                break;
            default:
                // all other input is invalid
                fprintf(stderr, "\n\n\n * * * Invalid selection: %d * * *\n\n\n", selection);
                break;
        }

        Finalize();
        Close(clientfd);
    } while(selection != EXIT_APPLICATION);

	exit(0);
}

// Add Garbarge to clean
void AddToFinalizeList(void *unit)
{
    if (Head == NULL) // 1 time setup of garbage collection
    {
        Head = (struct Garbage*)malloc(sizeof(struct Garbage));
        Head->Unit = NULL;
        Head->Next = NULL;
    }

    struct Garbage *New = (struct Garbage*)malloc(sizeof(struct Garbage));
    New->Unit = unit;
    New->Next = NULL;
    Head->Next = New;
}

// Free up dynamically created memory
void Finalize()
{
    struct Garbage *current = Head; // setup for freeing loop. node
    while(current != NULL)          // free up each item in the list
    {
        struct Garbage *temp = current; // prep item to be freeed
        current = current->Next;        // advance the current pointer
        free(temp->Unit);               // free up the item
        free(temp);                     // free up the container
    }
}

void SearchName(int clientfd)
{
    char bufferSizeBuffer[5],
        firstName[FIELD_SIZE],
        lastName[FIELD_SIZE],
        buffer[MAXLINE]; // The buffer is the max size needed to send to the service;

    printf("Please enter the first and last name: "); // get the name from the user
    scanf("%s %s",firstName, lastName);

    bzero(bufferSizeBuffer, 5); // setup buffer size to convert selection from int to char*
    sprintf(bufferSizeBuffer, "%d", SEARCH_NAME); // convert int to char*

    bzero(buffer, MAXLINE); // initialize the buffer for action

    strcat(buffer, bufferSizeBuffer); // setup the buffer to send to the database service
    strcat(buffer, ",");
    strcat(buffer, firstName);
    strcat(buffer, ",");
    strcat(buffer, lastName);
    strcat(buffer, ",0,0.0,-1"); // place holers for options not being used

    write(clientfd, buffer, MAXLINE); // send to the database service
    // wait for database service to send the success result
    bzero(buffer, MAXLINE);
    read(clientfd, buffer, MAXLINE);

    // wait for database service to send the search results response
    bzero(buffer, MAXLINE);
    read(clientfd, buffer, MAXLINE);

    if (strcmp(buffer, "Record not found!\n") != 0)
    {
        printf("Name            Department      Zip Code        Salary\n");
    }

    printf("%s\n", buffer);
}

void SearchZipCode(int clientfd)
{
    char bufferSizeBuffer[5],
        zipCode[6],
        buffer[MAXLINE]; // The buffer is the max size needed to send to the service;

    printf("Please enter the zip code: "); // get the name from the user
    scanf("%s", zipCode);

    bzero(bufferSizeBuffer, 5); // setup buffer size to convert selection from int to char*
    sprintf(bufferSizeBuffer, "%d", SEARCH_ZIP_CODE); // convert int to char*

    bzero(buffer, MAXLINE); // initialize the buffer for action
    strcat(buffer, bufferSizeBuffer); // setup the buffer to send to the database service
    strcat(buffer, ",NA,NA,"); // place holers for options not being used
    strcat(buffer, zipCode);
    strcat(buffer, ",0.0,-1"); // place holers for options not being used

    write(clientfd, buffer, MAXLINE); // send to the database service

    // wait for database service to send the success result
    bzero(buffer, MAXLINE);
    read(clientfd, buffer, MAXLINE);

    // wait for database service to send the search results response
    bzero(buffer, MAXLINE);
    read(clientfd, buffer, MAXLINE);

    if (strcmp(buffer, "Record not found!\n") != 0)
    {
        printf("Name            Department      Zip Code        Salary\n");
    }

    printf("%s\n", buffer);

}

void SearchSalary(int clientfd)
{
    char bufferSizeBuffer[5],
        salary[FIELD_SIZE],
        sCompType[3],
        compType[2] = { '\0', '\0' },
        buffer[MAXLINE]; // The buffer is the max size needed to send to the service;

    printf("Please enter the salary: ");
    scanf("%s", salary);
    printf("Please enter the Comparision Type ['>','<','==','>=','<=']: ");
    scanf("%s", sCompType);

    if (strcmp(sCompType, ">") == 0)
    {
        compType[0] = GT;
    }
    else if (strcmp(sCompType, "<") == 0)
    {
        compType[0] = LT;
    }
    else if (strcmp(sCompType, "==") == 0)
    {
        compType[0] = EQ;
    }
    else if (strcmp(sCompType, ">=") == 0)
    {
        compType[0] = GTE;
    }
    else if (strcmp(sCompType, "<=") == 0)
    {
        compType[0] = LTE;
    }

    bzero(bufferSizeBuffer, 5); // setup buffer size to convert selection from int to char*
    sprintf(bufferSizeBuffer, "%d", SEARCH_SALARY); // convert int to char*

    bzero(buffer, MAXLINE); // initialize the buffer for action
    strcat(buffer, bufferSizeBuffer); // setup the buffer to send to the database service
    strcat(buffer, ",NA,NA,0,"); // place holers for options not being used
    strcat(buffer, salary);
    strcat(buffer, ",");
    strcat(buffer, compType);

    write(clientfd, buffer, MAXLINE); // send to the database service

    // wait for database service to send the success result
    bzero(buffer, MAXLINE);
    read(clientfd, buffer, MAXLINE);

    // wait for database service to send the search results response
    bzero(buffer, MAXLINE);
    read(clientfd, buffer, MAXLINE);

    if (strcmp(buffer, "Record not found!\n") != 0)
    {
        printf("Name            Department      Zip Code        Salary\n");
    }

    printf("%s\n", buffer);
}

void AddRecord(int clientfd)
{
    char firstName[FIELD_SIZE];
    char lastName[FIELD_SIZE];
    char department[FIELD_SIZE];
    char zipCode[FIELD_SIZE];
    char salary[FIELD_SIZE];
    char buffer[MAXLINE];

    printf("Please enter the first name: "); // get employee data.
    scanf("%s", firstName);
    printf("Please enter the last name: ");
    scanf("%s", lastName);
    printf("Please enter the zip code: ");
    scanf("%s", zipCode);
    printf("Please enter the department: ");
    scanf("%s", department);
    printf("Please enter the salary: ");
    scanf("%s", salary);

    bzero(buffer, MAXLINE); // build request string
    strcat(buffer,"1");
    strcat(buffer,",");
    strcat(buffer,firstName);
    strcat(buffer,",");
    strcat(buffer,lastName);
    strcat(buffer,",");
    strcat(buffer,zipCode);
    strcat(buffer,",");
    strcat(buffer,department);
    strcat(buffer,",");
    strcat(buffer,salary);

    write(clientfd, buffer, MAXLINE); // send to the database service

    bzero(buffer, MAXLINE);
    read(clientfd, buffer, MAXLINE);
    printf("%s\n", buffer);
}