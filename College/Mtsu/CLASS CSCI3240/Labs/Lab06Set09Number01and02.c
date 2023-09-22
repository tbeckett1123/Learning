/* Name: 	Timothy Beckett
 * Lab:		6
 * Set:		9
 * Number:	1
 * Description: Write a program to read a file named “record.csv,” which contains the employee’s
 * Name, Zip code, Department, and Salary information. Your program should store
 * the information from the “record.csv” file into a structure Struct_Employee_Info
 * (with members: First Name, Last Name, Zip code, Department, and Salary). Next,
 * add the following functionalities.
 *   a. SearchByName function: This function should take three arguments:
 *      “employeeStructure”, “firstName” and “lastName.” The function should
 *      search the structure to find the matching records by full name. The function
 *      should return all the matching records to the caller function (main function).
 *      The caller function should then display the result.
 *   b. SearchByZipCode function: This function should take two arguments:
 *      “employeeStructure” and “zipCode.” The function should search the
 *      structure to find all the employees who live in the provided zip code. The
 *      function should return all the matching records to the caller function. The
 *      caller function should then display the result.
 *   c. SearchBySalary function: This function should take three arguments
 *      “employeeStructure”, “salary”, and “comparisonOperator”. The
 *      comparison operator contains one of the operators in the set: {“>”, “<”,”>=”,
 *      “<=”, “==”}. Example scenarios:
 *         i. If the “salary” value is 50,000 and the “comparisionOperator” is “>=”,
 *            your function should find all the employees whose salary is greater
 *            than or equal to 50,000.
 *        ii. Similarly, if the “salary” value is 40,000 and the
 *            “comparisionOperator” is “==”, your function should find all the
 *            employees whose salary is equal to 40,000.
 *       iii. The function should return all the matching records to the caller
 *            function. The caller function should then display the result.
 *
 * Sample contents of records.csv file:
 * Pablo,Picasso,37128,Arts,65000
 * Jack,Sparrow,07801,Movies,40000
 * Jackie,Chan,12345,Martial Arts,50000
 * Charles,Babbage,37128,Computer Science,55000
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define FIELD_SIZE 128
#define LINE_SIZE 1024
#define BUFFER_SIZE 15

struct Struct_Employee_Info
{
    char FirstName[FIELD_SIZE];
    char LastName[FIELD_SIZE];
    char Department[FIELD_SIZE];
    int   ZipCode;
    double Salary;
    struct Struct_Employee_Info *Next;
};

// Structure way of tracking dynamic memory to free before ending program
struct Garbage
{
    void *Unit;
    struct Garbage *Next;
} *Head = NULL;
void AddToFinalizeList(void *unit);
void Finalize();

int LineCount(FILE *fptr);
void LoadDatabase(char *filename, struct Struct_Employee_Info **employees);
char* SearchName(struct Struct_Employee_Info *employees, char *firstName, char *lastName);
char* SearchZipCode(struct Struct_Employee_Info *employees, int zipCode);
char* SearchSalary(struct Struct_Employee_Info *employees, double Salary);
void FormattedRow(struct Struct_Employee_Info *record, char* buffer, int *index);
char* FormattedValue(char *value);
void AddCommas(char* str);

int main(int argc, char** argv)
{    
    char filename[] = "records.csv";
    struct Struct_Employee_Info *employees = NULL;
    int zipCode;
    double salary;
    char firstName[FIELD_SIZE], lastName[FIELD_SIZE];
    char *results;
    
    LoadDatabase(filename, &employees);   
    
    bzero(firstName, FIELD_SIZE);
    bzero(lastName, FIELD_SIZE);
    
    printf("Enter a first and last name:\n");
    scanf("%s %s", firstName, lastName);
    
    results = SearchName(employees, firstName, lastName);

    printf("Name            Department      Zip Code        Salary\n");
    printf("%s\n", results);
    
    printf("Enter a zip code:\n");
    scanf("%d", &zipCode);
    
    results = SearchZipCode(employees, zipCode);
    
    printf("Name            Department      Zip Code        Salary\n");
    printf("%s\n", results);
    
    printf("Enter a salary:\n");
    scanf("%lf", &salary);
    
    results = SearchSalary(employees, salary);
    
    printf("Name            Department      Zip Code        Salary\n");
    printf("%s\n", results);
    
    Finalize();

    return 0;
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
void LoadDatabase(char *filename, struct Struct_Employee_Info **employees)
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
        AddToFinalizeList(employee);  // add employee record to tracked garbage collection
        
        bzero(line, LINE_SIZE); // reset the line buffer                    
    }        
    
    fclose(fptr);
}

// Search for records matching the first and last names
// returns a formatted string of the matches seperated by newlines
char* SearchName(struct Struct_Employee_Info *employees, char *firstName, char *lastName)
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
        tSize = sizeof(char) * (count * 66) + 1;  // Calculate the size of the matches size
        matches = (char*)malloc(tSize);           // 65 is the length of the formatted row
                                                  // plu1 1 character for a newline and
                                                  // 1 character for the NULL termerator
        AddToFinalizeList(matches);               // Add matching records string to tracked garbage collection
                                
        //clear the buffer
        bzero(matches, tSize);                                   

        // find the matching records and create a formatted string with the results.
        current = employees;
        while (current != NULL)
        {
            if (strcmp(firstName, current->FirstName) == 0 && strcmp(lastName, current->LastName) == 0)
            {
                FormattedRow(current, matches, &i);
            }
        
            current = current->Next;
        }

        matches[i+1] = '\0'; // null terminate result string.
    }
    
    return matches;
}

// Search for records matching the zip code
// returns a formatted string of the matches seperated by newlines
char* SearchZipCode(struct Struct_Employee_Info *employees, int zipCode)
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
        AddToFinalizeList(matches);               // Add matching records string to tracked garbage collection
                                
        //clear the buffer
        bzero(matches, tSize);

        // find the matching records and create a formatted string with the results.
        current = employees;
        while (current != NULL)
        {
            if (zipCode == current->ZipCode)            
                FormattedRow(current, matches, &i);
                    
            current = current->Next;
        }

        matches[i+1] = '\0'; // null terminate result string.
    }
    
    return matches;
}

// Search for records matching the salary
// returns a formatted string of the matches seperated by newlines
char* SearchSalary(struct Struct_Employee_Info *employees, double salary)
{
    struct Struct_Employee_Info *current = employees;
    char* matches = NULL;
    int count = 0, i = 0, tSize;
    int iSalary = (int)(100.0 * salary); // shift the 10-1 and 10-2 places left and cast to int to trucate odd fractional values.
    
    // find the number of matches
    while (current != NULL) 
    {
        if (iSalary == (int)(100.0 * current->Salary))
            count++;
        
        current = current->Next;
    }

    if (count != 0)
    {
        tSize = sizeof(char) * (count * 66) + 1;  // Calculate the size of the matches size
        matches = (char*)malloc(tSize);           // 65 is the length of the formatted row
                                                  // plu1 1 character for a newline and
                                                  // 1 character for the NULL termerator
        AddToFinalizeList(matches);               // Add matching records string to tracked garbage collection
                                
        //clear the buffer
        bzero(matches, tSize);                                   

        // find the matching records and create a formatted string with the results.
        current = employees;
        while (current != NULL)
        {
            if (iSalary == (int)(100.0 * current->Salary))
                FormattedRow(current, matches, &i);
                    
            current = current->Next;
        }

        matches[i+1] = '\0'; // null terminate result string.
    }
    
    return matches;
}

// Concatinates a formatted employee record string the the string buffer.
char nameBuffer[FIELD_SIZE * 2 + 1];
char salaryBuffer[10];
void FormattedRow(struct Struct_Employee_Info *record, char* buffer, int *index)
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
    AddCommas(salaryBuffer);

    *index += sprintf(buffer + *index, "$%-s\n", FormattedValue(salaryBuffer));    

}
                                
// printing a substring of the value for tabular data.
char buffer[BUFFER_SIZE]; // I needed a buffer that would allow me to return a substring
char* FormattedValue(char *value)
{

    int sLength = strlen(value);

    // if the value is less within the column length return.
    if (sLength <= BUFFER_SIZE) 
        return value;

    // setup formatted name
    //clear the buffer
    bzero(buffer, BUFFER_SIZE);    

    // the 3 dots indicates the value has been trucated for column
    strncpy(buffer, value, BUFFER_SIZE - 4);
    strcat(buffer, "...");

    return buffer;
}

//Format the decimal number with commas.
void AddCommas(char* str) 
{
    int len = strlen(str);
    int commaCount = (len - 1) / 3;     // Calculate the number of commas needed
    int newLen = len + commaCount;      // Calculate the new length of the string
    char* newStr = malloc(newLen + 1);  // Allocate memory for the modified string
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

    str[j] = '\0';              // Null terminate the modified string
    AddToFinalizeList(newStr); // Add buffer string to tracked garbage collection
}