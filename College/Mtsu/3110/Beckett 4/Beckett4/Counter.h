/*
Programmer:		Timothy Beckett
Class:			CSCI 3110
Instructor:		Dr. Seo
File:			Counter.h
*********************************************
Description: The purpose of this class is to
protect a count from tampering. It counts on 
demand using the ++ operator. By default it 
will start the count at zeor. However, you 
can start the count at whatever value you want.  
You can also copy another counter into it.  
It has the ability to print the count directly
to the screen using the << operator.  It has
the ability to reset to the initial value using
the Reset, and it can return the value of the
count using Return.  It also has the ability to
do comparisons agianst other Counters and ints
using the >, <, and == operators.
*/

# include <iostream>

using namespace std;

# ifndef COUNTER_H
# define COUNTER_H

class Counter
{
//friend functions

	//Overloaded output operator
	//Preconditions:	expects a 
	//					ostream and a Counter
	//Postconditions:	the count will be 
	//					displayed to the screen
	friend ostream& operator<<(ostream&, const Counter&);

public:
	
	//default constructor
	//Preconditions:	None
	//Postconditions:	count and reset will be zero
	Counter();

	//initialize constructor
	//Preconditions:	expects an int
	//Postconditions:	count and reset
	//					will be set equal
	//					to the provided int
	Counter(const int);

	//copy constructor
	//Preconditions:	expects a Counter
	//Postconditions:	this count will be
	//					equal to the provided
	//					Counter count
	//					this reset will be
	//					equal to the provided
	//					Counter reset
	Counter(const Counter&);

	//overloaded increment operator
	//Preconditions:	None
	//Postconditions:	None
	void operator++();

	//this method will return the value
	//stored in count
	//Preconditions:	None
	//Postconditions:	None
	int Return() const;

	//this method will restore the
	//count back to initial value
	//Preconditions:	None
	//Postconditions:	None
	void Reset();

	//overloaded comparison operators
	
	//Compares two Counter and determines
	//if the l value is less the r value
	//Preconditions:	accepts a Counter
	//					as the r value
	//Postcondtions:    returns true if
	//					if the l value is
	//					less than the 
	//					r value otherwise
	//					it return false.
	bool operator<(const Counter&) const;

	//Compares two Counter and determines
	//if the l value is greaterthe r value
	//Preconditions:	accepts a Counter
	//					as the r value
	//Postcondtions:    returns true if
	//					if the l value is
	//					greater than the 
	//					r value otherwise
	//					it return false.
	bool operator>(const Counter&) const;
	
	//Compares two Counter and determines
	//if the l value is equal to the r value
	//Preconditions:	accepts a Counter
	//					as the r value
	//Postcondtions:    returns true if
	//					if the l value is
	//					equal to the 
	//					r value otherwise
	//					it return false.	
	bool operator==(const Counter&) const;

	//Compares this counter to and int
	//if the l value is less the r value
	//Preconditions:	accepts a int
	//					as the r value
	//Postcondtions:    returns true if
	//					if the l value is
	//					less than the 
	//					r value otherwise
	//					it return false.
	bool operator<(const int&) const;

	//Compares this counter to and int
	//if the l value is greater the r value
	//Preconditions:	accepts a int
	//					as the r value
	//Postcondtions:    returns true if
	//					if the l value is
	//					greater than the 
	//					r value otherwise
	//					it return false.
	bool operator>(const int&) const;

	//Compares this counter to and int
	//if the l value is equal to the r value
	//Preconditions:	accepts a int
	//					as the r value
	//Postcondtions:    returns true if
	//					if the l value is
	//					equal to the 
	//					r value otherwise
	//					it return false.
	bool operator==(const int&) const;


private:
	int count,
		reset;
};
# endif //COUNT_H