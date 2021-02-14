/*
Programmer:	Timothy Beckett
Class:		CSCI 3110
Instructor:	Dr. Seo

This program implements to classes, Employee and LinkedList.
The purpose of the program:
This program will read a list of Employee records from a file
and will populated the LinkedList with the records.  It will
allow the user to edit the list as nessary.  The available
options are print the list of employee records, add an 
employee, delete an employee, find an employee and display
the record if it is found in the list.  After the user has
finished working with the list.  The revised list will be 
written to a file.  The user will be prompted for the 
file name.
*/
# include "Employee.h"
# include "LinkedList.h"
# include "impLinkedList.cpp"
# include <fstream>

using namespace std;

void readFile(LinkedList<Employee> &);
void writeFile(LinkedList<Employee>&);
void printEmployee(LinkedList<Employee>&);
void addEmployee(LinkedList<Employee>&);
void findEmployee(LinkedList<Employee>&);
void deleteEmployee(LinkedList<Employee>&);

int main()
{
	LinkedList<Employee> employeeList;
	char select;

	readFile(employeeList);

	do
	{
		system("cls");

		cout<<"Menu:\n"
			<<"1.	Print all Employees\n"
			<<"2.	Add an employee\n"
			<<"3.	Find an employee\n"
			<<"4.	Delete an employee\n"
			<<"5.	Quit\n"
			<<"Enter your selection(1-5): ";
		cin>>select;
		
		switch(select)
		{
		case '1': printEmployee(employeeList); break;
		case '2': addEmployee(employeeList); break;
		case '3': findEmployee(employeeList); break;
		case '4': deleteEmployee(employeeList); break;
		case '5': writeFile(employeeList); break;
		default: cout<<"Invalid Selection\n";
				 system("pause");
		};
	}while(select != '5');

	cout<<"Thank you -- good bye\n";

	return 0;
}
/*
This function reads a list of employee records from
a file and puts them into a linked list that the 
user can edit.

Precondtions:	The calling function must provide
				the LinkedList for building
Postcondtions:	The list will be populated with
				the employee records.
*/
void readFile(LinkedList<Employee>& ptrEmployeeList)
{
	ifstream myfile;
	Employee temp;


	myfile.open("employees.dat");

	if(!myfile)
	{
		cerr<<"employess.dat is unavailable\n";
		exit(1);
	}
	
	myfile>>temp;

	for(int i = 0; myfile; i++)
	{
	ptrEmployeeList.ins(temp, i);
	myfile>>temp;	
	}
	
	myfile.close();
}

/*
This fucntion gets a file name from the user, and
writes the list to the file.

Preconditions:	the calling fuction must provide
				the LinkedList for editing.
Postconditions:	a new file will be created and 
				the list will be written to it
*/
void writeFile(LinkedList<Employee>& ptrEmployeeList)
{
	ofstream myfile;
	Employee record;
	string first, last, filename;
	int ssn, listSize;
	double salary;

	cout<<"enter the output file name\n";
	cin>>filename;

	myfile.open(filename.c_str());

	listSize = ptrEmployeeList.size();

	for(int i = 0; i < listSize; i++)
	{
		ptrEmployeeList.get(record, i);
		record.get(first);
		record.get(last, LAST);
		record.get(ssn);
		record.get(salary);

		myfile<<first<<endl
			  <<last<<endl
			  <<ssn<<endl
			  <<salary<<endl;
	}
	
	myfile.close();
}

/*
This function will print the list to the screen

Preconditions:	the calling fucntion must provide
				the LinkedList
Postconditions:	None
*/
void printEmployee(LinkedList<Employee>& ptrEmployeeList)
{
	 Employee temp;
	 int listSize = ptrEmployeeList.size();
	system("cls");
	cout<<left<<setw(10)<<"First"<<setw(10)<<"Last"<<setw(10)<<"SSN"<<"Salary\n"<<right;
	cout<<setfill('-')<<setw(39)<<"-\n"<<setfill(' ');
	
	for(int index = 0; index < listSize; index++)
	{
		ptrEmployeeList.get(temp, index);
		cout<<temp<<endl;
	}
	system("pause");
}

/*
This method will add an employee record to the list

Preconditions:	The calling funciton must provide
				the LinkedList for editing
Postconditions:	None
*/
void addEmployee(LinkedList<Employee>& ptrEmployeeList)
{
	Employee temp;

	system("cls");

	cout<<"Enter the employee's information\n"
		<<"inorder\n First Last SSN Salary\n";
	cin>>temp;

	ptrEmployeeList.ins(temp, ptrEmployeeList.size());
}

/*
This fucntion will will find an employee record and
display the information to the user if the record is
found.  if it is not, the user will be ask if the
want to add the record.  if they do, addEmployee
will be called.

Preconditions:	The calling funciton must provide
				the LinkedList for editing
Postconditions:	None
*/
void findEmployee(LinkedList<Employee>& ptrEmployeeList)
{

	string first, last;
	Employee record;
	char choice;
	int index;
	
	system("cls");

	cout<<"Enter the employee's name (last first)\n";
	cin>>last>>first;

	record.set(first);
	record.set(last, LAST);

	if(ptrEmployeeList.get(index, record))
		ptrEmployeeList.get(record, index);
	else
	{
		cout<<"Employee not found\nDo you wish to create an Employee record(y/n)\n";
		cin>>choice;

		if(choice == 'y')
			addEmployee(ptrEmployeeList);
		else
			return;
	}
	
	system("cls");
	
	cout<<left<<setw(10)<<"First"<<setw(10)<<"Last"<<setw(10)<<"SSN"<<"Salary\n"<<right
		<<setfill('-')<<setw(39)<<"-\n"<<setfill(' ')
		<<record<<endl;

	system("pause");
}

/*
This method will remove the desired record from the list

Preconditions:	The calling funciton must provide
				the LinkedList for editing
Postconditions:	None
*/
void deleteEmployee(LinkedList<Employee>& ptrEmployeeList)
{
	Employee temp;
	string first, last;
	int index;

	system("cls");

	cout<<"Enter the employee's name (last first)\n";
	cin>>last>>first;

	temp.set(first);
	temp.set(last, LAST);

	if(ptrEmployeeList.get(index, temp))
		ptrEmployeeList.rem(index);
}