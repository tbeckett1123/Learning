/*
Programmer:	Timothy Beckett
File:		Person.h -- Person Class
Class:		CSCI 3110
Instructor:	Dr. Seo
*/

# include <iostream>
# include <iomanip>
# include <string>

using namespace std;

# ifndef PERSON_H
# define PERSON_H

class Person
{

	/*
	This overloade operator << will print to the screen
	the data in the provide Person object.
	
		Guidelines for displaying record
			Dispay all data on the Person
			Last name First name SSN Salary
			Allow 9 charators for all fields

	Preconditions:	The user must provide an Person object
					to be printed
	Postconditions:	This method will return an ostream &
	*/
	friend ostream& operator<<(ostream&, const Person&);

	/*
	This overloaded operator >> will get the required data
	from the user.

	Preconditions:	The user must provide an Person object
					to store the data in
	Postconditions:	This method will return a istream &
	*/
	friend istream& operator>>(istream&, Person&);

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
	Person();
	
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
	Person(const string &, const string &,
		     const int &);
	/*
	Copy constructor:	This constructor will copy the data
						from the provided object to the new
						object.
    Preconditions:		The user must provide an object to copy
	Postconditions:		The new object will be equal to the
						original object.
						This method has no return conditions
	*/
	Person(const Person &);
	
	/*
	This get method will retreive the Persons first name
	
	Precondition:	The user must provide a string variable
					for the first name to be stored in.
	Postconditions:	The first name of the Person will be 
					stored in the the provide varialbe if
					it has be set by the user
					if the operation is successful the 
					method will return true otherwise it 
					will return false
	*/
	bool getf(string &);

	/*
	This get method will retreive the Persons last name

	Precondition:	The user must provide a string variable
					for the last name to be stored in; furthmore,
					the user must select this method by using the
					key word LAST.
	NOTE:			LAST is defined as a char with the value of 'L'
					Any char can be used in its place
	Postconditions:	The last name of the Person will be 
					stored in the the provide varialbe if
					it has be set by the user
					if the operation is successful the 
					method will return true otherwise it 
					will return false
	*/
	bool getl(string &);

	/*
	This get method will retreive the Persons ssn

	Precondition:	The user must provide an int variable
					for the ssn to be stored in.
	Postconditions:	The ssn of the Person will be 
					stored in the the provide varialbe if
					it has be set by the user
					if the operation is successful the 
					method will return true otherwise it 
					will return false
	*/
	bool gets(int &);

	/*
	This set function will set the Persons first name

	Preconditions:	The user must provide a string
					with the Persons name in it.
	Postconditions:	The object string variable first will be 
					set to the provided string.
					This method has no return value
	*/
	void setf(const string &);

	/*
	This set function will wet the Persons last name

	Preconditions:	The user must provide a string
					with the Persons last name in it	
	Postconditions:	The object string variable last will be set
					to the provided string
					This method has no return value
	*/
	void setl(const string &);

	/*
	This set method will set the Persons ssn

	Preconditions:	The user must provide an int
	Postconditions:	The object int ssn will be set to
					the provided int
					This method has no return value
	*/
	void sets(const int &);

	/*
	This overload operator == will compare to
	Person objects to determine if first and
	last names are equal.

	preconditions:	The user must provide an 
					Person object
	postconditions:	this method will return true
					if the names are the same
					otherwise it will return false
	*/
	bool operator==(const Person &);
	
	/*
	This overloaded operator = will assign the values
	of one Person object to the new one.

	Precoditions:	The user must provide an Person object
					to copy.
	Postcoditions:	this object will be a copy of the provided
					object.
					This method returns a copy of the provided
					object.
	*/
	const Person& operator=(const Person &);

	/*
	This method will determine if the L value Person is less
	than the R value Person

	Preconditions:	The calling method must proved a Person obj
	Postconditions:	if this obj is less than the provided obj
					it will return true.
					if this obj is greater than the provided obj
					it will return false.
	*/
	bool operator<(Person &) const;

	/*
	This method displays the objects info

	Preconditions:	None
	Postconditions:	None
	*/
	virtual void display();

	/*
	This method prompts the user for the first name, last name
	and ssn

	Preconditions:	None
	Postconditions:	The object will store the provided 
					information
	*/
	virtual void read();

	/*
	This method returns a char the indecates the object type

	Preconditions:	None
	Postconditions:	returns the char 'p'
	*/
	virtual char id();



protected:
	string first, last;
	int ssn;
};
# endif