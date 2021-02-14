/*
Programmer:	Timothy Beckett
File:		StudentWorker.h -- StudentWorker Class
Class:		CSCI 3110
Instructor:	Dr. Seo
*/
# include "Student.h"

# ifndef STUDENTWORK_H
# define STUDENTWORK_H

class StudentWorker: public Student
{
// * * * * Friend Functions * * * *

	friend ostream& operator<<(ostream&, StudentWorker&);
	friend istream& operator>>(istream&, StudentWorker&);

public:

// * * * * Constructors * * * *
	
	//default constuctor
	StudentWorker();

	//copy constuctor
	StudentWorker(const StudentWorker&);

	//initialize constructor
	StudentWorker(string, string, int, float,
				float, SortedLinkedList<Course*>);

// * * * * class methods * * * *

	/*
	This method will return the salary
	Preconditions:	hours and rate must
					be intialized
	Postconditions:	None
	*/
	float Salary();

// * * * * virtual methods * * * *

	/*
	This method displays the objects info

	Preconditions:	None
	Postconditions:	None
	*/
	virtual void display();

	/*
	This method prompts the user for the first name, last name
	and ssn, gpa, and course

	Preconditions:	None
	Postconditions:	The object will store the provided 
					information
	*/
	virtual void read();

	/*
	This method returns a char the indecates the object type

	Preconditions:	None
	Postconditions:	returns the char 'w'
	*/
	virtual char id();

// * * * * Overloaded Operators * * * *

	bool operator<(const StudentWorker&);

	bool operator==(const StudentWorker&);

	StudentWorker& operator=(StudentWorker&);



//*********************public data members*********************** 

	//use the = operator to assign public data members
	float hours, rate;

	/*****************************************
		Data inheritaned from Student Class
		
		string first, last
		int ssn

	******************************************/


/* * * * * Available from Student Class * * * * 

	//The SortedLinkedList<T> will protect
	//the data from tampering by a user.	
	//See the SortedLinkedList.h for 
	//available methods and features
	//									
	SortedLinkedList<Course> CourseList;

	
	//This method returns the gpa to the user.
	//It will calculate the gpa if needed.
	//
	//Preconditions:	None
	//Postconditions:	The methdo will return the gpa.
	//				If the gpa has not been assigned
	//				a -1.0 will be returned.
	//
	float Gpa();

**************************************************************/
protected:

// * * * * protected class method * * * *
	void calcSal();

	float salary;
	
	// Inherited from Student Class
	//float gpa
};

#endif