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
#include <ctype.h>
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
int IsNumber(const char* str);

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
        scanf(" %d", &selection);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
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

    bzero(firstName, FIELD_SIZE);
    bzero(lastName, FIELD_SIZE);

    printf("Please enter the first name: "); // get the name from the user
    fgets(firstName, FIELD_SIZE, stdin);
    firstName[strcspn(firstName, "\n")] = '\0';
    printf("Please enter the last name: "); // get the name from the user
    fgets(lastName, FIELD_SIZE, stdin);
    lastName[strcspn(lastName, "\n")] = '\0';

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

    bzero(zipCode, 6);
    printf("Please enter the zip code: "); // get the name from the user
    fgets(zipCode, 6, stdin);
    zipCode[strcspn(zipCode, "\n")] = '\0';

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

    bzero(salary, FIELD_SIZE); 
    printf("Please enter the salary: ");
    fgets(salary, FIELD_SIZE, stdin);
    salary[strcspn(salary, "\n")] = '\0';
    while(0 == IsNumber(salary))
    {
        bzero(salary, FIELD_SIZE);
        printf("Invalid Input\n");
        printf("Please enter the salary: ");
        fgets(salary, FIELD_SIZE, stdin);
        salary[strcspn(salary, "\n")] = '\0';
    }

    int e;

    do
    {
        e = 0;
        bzero(sCompType, 3);
        printf("Please enter the Comparision Type ['>','<','==','>=','<=']: ");
        fgets(sCompType, 3, stdin);
        sCompType[strcspn(sCompType, "\n")] = '\0';
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
        else
        {
            printf("Invalid Input\n");
            e = 1;
        }
    }while(e == 1);


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

int IsNumber(const char* str) {
    int isNumber = 1;

    for(int i = 0; i < strlen(str); i++)
        if (!isdigit(str[i]) && str[i] != '.')
            isNumber = 0;

    return isNumber;
}

void AddRecord(int clientfd)
{
    char firstName[FIELD_SIZE];
    char lastName[FIELD_SIZE];
    char department[FIELD_SIZE];
    char zipCode[FIELD_SIZE];
    char salary[FIELD_SIZE];
    char buffer[MAXLINE];

    bzero(firstName, FIELD_SIZE);
    bzero(lastName, FIELD_SIZE);
    bzero(department, FIELD_SIZE);
    bzero(zipCode, FIELD_SIZE);
    bzero(salary, FIELD_SIZE);

    printf("Please enter the first name: "); // get employee data.
    fgets(firstName, FIELD_SIZE, stdin);
    firstName[strcspn(firstName, "\n")] = '\0';

    printf("Please enter the last name: ");
    fgets(lastName, FIELD_SIZE, stdin);
    lastName[strcspn(lastName, "\n")] = '\0';

    printf("Please enter the zip code: ");
    fgets(zipCode, FIELD_SIZE, stdin);
    zipCode[strcspn(zipCode, "\n")] = '\0';

    while(0 == IsNumber(zipCode))
    {
        bzero(zipCode, FIELD_SIZE);
        printf("Invalid Input\n");
        printf("Please enter the zip code: ");
        fgets(zipCode, FIELD_SIZE, stdin);
        zipCode[strcspn(zipCode, "\n")] = '\0';
    }

    printf("Please enter the department: ");
    fgets(department, FIELD_SIZE, stdin);
    department[strcspn(department, "\n")] = '\0';

    printf("Please enter the salary: ");
    fgets(salary, FIELD_SIZE, stdin);
    salary[strcspn(salary, "\n")] = '\0';

    while(0 == IsNumber(salary))
    {
        bzero(salary, FIELD_SIZE);
        printf("Invalid Input\n");
        printf("Please enter the salary: ");
        fgets(salary, FIELD_SIZE, stdin);
        salary[strcspn(salary, "\n")] = '\0';
    }

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