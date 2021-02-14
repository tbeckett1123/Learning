/*
Programmer:	Timothy Beckett
File:		Employee.h -- Employee Class
Class:		CSCI 3110
Instructor:	Dr. Seo
*/

# include <iostream>
# include <iomanip>
# include <string>

using namespace std;

# ifndef EMPLOYEE_H
# define EMPLOYEE_H
# define LAST 'L'

class Employee
{

	/*
	This overloade operator << will print to the screen
	the data in the provide employee object.
	
		Guidelines for displaying record
			Dispay all data on the employee
			Last name First name SSN Salary
			Allow 9 charators for all fields

	Preconditions:	The user must provide an employee object
					to be printed
	Postconditions:	This method will return an ostream &
	*/
	friend ostream& operator<<(ostream&, const Employee&);

	/*
	This overloaded operator >> will get the required data
	from the user.

	Preconditions:	The user must provide an employee object
					to store the data in
	Postconditions:	This method will return a istream &
	*/
	friend istream& operator>>(istream&, Employee&);

public:
	/*
	Defualt constructor
	Pre conditions:	 None
	Post conditions: First Name will be set to nobody
					 Last Name will be set to nobody
					 SSN will be set to 0
					 salary will be set to -1.0
					 This method has no return values
	*/
	Employee();
	
	/*
	Intialize constructor:  This constructor will allow
	the user to set the data values in the class
	Pre conditions:	user must provide in this order
					two strings, a whole number, and
					a decimal number.
	Post conditions:The data members will be intialized
					to the provided data values
					This method has no return value
	*/
	Employee(const string &, const string &,
		     const int &, const double &);
	/*
	Copy constructor:	This constructor will copy the data
						from the provided object to the new
						object.
    Preconditions:		The user must provide an object to copy
	Postconditions:		The new object will be equal to the
						original object.
						This method has no return conditions
	*/
	Employee(const Employee &);
	
	/*
	This get method will retreive the employees first name
	
	Precondition:	The user must provide a string variable
					for the first name to be stored in.
	Postconditions:	The first name of the employee will be 
					stored in the the provide varialbe if
					it has be set by the user
					if the operation is successful the 
					method will return true otherwise it 
					will return false
	*/
	bool get(string &);

	/*
	This get method will retreive the employees last name

	Precondition:	The user must provide a string variable
					for the last name to be stored in; furthmore,
					the user must select this method by using the
					key word LAST.
	NOTE:			LAST is defined as a char with the value of 'L'
					Any char can be used in its place
	Postconditions:	The last name of the employee will be 
					stored in the the provide varialbe if
					it has be set by the user
					if the operation is successful the 
					method will return true otherwise it 
					will return false
	*/
	bool get(string &, const char &);

	/*
	This get method will retreive the employees ssn

	Precondition:	The user must provide an int variable
					for the ssn to be stored in.
	Postconditions:	The ssn of the employee will be 
					stored in the the provide varialbe if
					it has be set by the user
					if the operation is successful the 
					method will return true otherwise it 
					will return false
	*/
	bool get(int &);

	/*
	This get method will retreive the employees salary

	Precondition:	The user must provide a double variable
					for the salary to be stored in.
	Postconditions:	The salary of the employee will be 
					stored in the the provide varialbe if
					it has be set by the user
					if the operation is successful the 
					method will return true otherwise it 
					will return false
	*/
	bool get(double &);

	/*
	This set function will set the employees first name

	Preconditions:	The user must provide a string
					with the employees name in it.
	Postconditions:	The object string variable first will be 
					set to the provided string.
					This method has no return value
	*/
	void set(const string &);

	/*
	This set function will wet the employees last name

	Preconditions:	The user must provide a string
					with the employees last name in it
					followed by the key word LAST	
	NOTE:			LAST is defined as a char with the value of 'L'
					Any char can be used in its place
	Postconditions:	The object string variable last will be set
					to the provided string
					This method has no return value
	*/
	void set(const string &, const char &);

	/*
	This set method will set the employees ssn

	Preconditions:	The user must provide an int
	Postconditions:	The object int ssn will be set to
					the provided int
					This method has no return value
	*/
	void set(const int &);

	/*
	This set method will set the employees salary

	Preconditions:	the user must provide a double
					variable
	Postconditions: The object double variable will 
					be set to the provide double
					This method has no return value
	*/
	void set(const double &);

	/*
	This overload operator == will compare to
	Employee objects to determine if first and
	last names are equal.

	preconditions:	The user must provide an 
					employee object
	postconditions:	this method will return true
					if the names are the same
					otherwise it will return false
	*/
	bool operator==(const Employee &);
	
	/*
	This overloaded operator = will assign the values
	of one employee object to the new one.

	Precoditions:	The user must provide an employee object
					to copy.
	Postcoditions:	this object will be a copy of the provided
					object.
					This method returns a copy of the provided
					object.
	*/
	const Employee& operator=( const Employee &);

private:
	string first, last;
	int ssn;
	double salary;
};
# endif