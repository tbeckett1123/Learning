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
// * * * * Friend functions * * * * 
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

// * * * * Constructors * * * * 

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
	
// * * * * Overloaded Operators * * * * 

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

// * * * * Data members * * * * 

	//use = operator as geter and seter for all data members
	string	first,	//First Name
			last;	//Last Name
	int		ssn;	//Social Security Number
};
# endif