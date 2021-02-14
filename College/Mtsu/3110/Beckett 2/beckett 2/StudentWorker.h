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
	StudentWorker(StudentWorker&);

	//initialize constructor
	StudentWorker(string, string, int, float, float,
				float, SortedLinkedList<Course*>);

// * * * * class methods * * * *

	/*
	This method will put the pay rate and
	put it in the provided reference variable
	
	Preconditions:	the calling method must
					provide a float to store
					the rate in.
	Postconditions:	if the operation is suc-
					cessful the method will
					return true and the rate
					will be in the provided
					float otherwise the
					method will return false
					and the provided float
					will be unchanged.
	*/
	bool getr(float&);
	/*
	This method will put the hours worked and
	put it in the provided reference variable
	
	Preconditions:	the calling method must
					provide a float to store
					the hours in.
	Postconditions:	if the operation is suc-
					cessful the method will
					return true and the hours
					will be in the provided
					float otherwise the
					method will return false
					and the provided float
					will be unchanged.
	*/
	bool geth(float&);
	/*
	This method will put the Salary and
	put it in the provided reference variable
	
	This method will also calculate the Salary
	if the rate or hours is changed
	
	Preconditions:	the calling method must
					provide a float to store
					the salary in.
					To get a salary calculation
					the rate or hours must be
					changed
	Postconditions:	if the operation is suc-
					cessful the method will
					return true and the hours
					will be in the provided
					float otherwise the
					method will return false
					and the provided float
					will be unchanged.
	*/
	bool getSal(float&);

	/*
	This method will set the pay rate of the
	student

	Preconditions:	the calling method must
					provide the pay rate
					(a floating point #)
	Postconditions:	the provided value will
					be store as the pay rate
	*/
	void setr(float);

	/*
	This method will set the hours worked
	of the student

	Preconditions:	the calling method must
					provide the hours worked
					(a floating point #)
	Postconditions:	the provided value will
					be store as the hours worked
	*/
	void seth(float);
	

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

// * * * * Available from Student Class * * * * 
/*
	************** bool getf(string &); ************************
		This get method will retreive the Students first name
	
	Precondition:	The user must provide a string variable
					for the first name to be stored in.
	Postconditions:	The first name of the Student will be 
					stored in the the provide varialbe if
					it has be set by the user
					if the operation is successful the 
					method will return true otherwise it 
					will return false
	************************************************************
	
	****************** bool getl(string &); ********************
	This get method will retreive the Students last name

	Precondition:	The user must provide a string variable
					for the last name to be stored in; furthmore,
					the user must select this method by using the
					key word LAST.
	NOTE:			LAST is defined as a char with the value of 'L'
					Any char can be used in its place
	Postconditions:	The last name of the Student will be 
					stored in the the provide varialbe if
					it has be set by the user
					if the operation is successful the 
					method will return true otherwise it 
					will return false
	************************************************************

	**********************bool gets(int &);*********************	
	This get method will retreive the Students ssn

	Precondition:	The user must provide an int variable
					for the ssn to be stored in.
	Postconditions:	The ssn of the Student will be 
					stored in the the provide varialbe if
					it has be set by the user
					if the operation is successful the 
					method will return true otherwise it 
					will return false
	************************************************************

	********************void setf(const string &);**************
	This set function will set the Students first name

	Preconditions:	The user must provide a string
					with the Students name in it.
	Postconditions:	The object string variable first will be 
					set to the provided string.
					This method has no return value
	************************************************************
	
	********************void setl(const string &);**************
	This set function will wet the Students last name

	Preconditions:	The user must provide a string
					with the Students last name in it	
	Postconditions:	The object string variable last will be set
					to the provided string
					This method has no return value
	************************************************************
	
	*******************void sets(const int &);******************
	This set method will set the Students ssn

	Preconditions:	The user must provide an int
	Postconditions:	The object int ssn will be set to
					the provided int
					This method has no return value
	************************************************************
	
	******************bool getg(float&);************************
	The getg method will assign a provided float
	with the current gpa
	Preconditions:	The caller must provide a float
	Postconditions:	The provided float will be 
					assigned a copy of the gpa
					if the operation is successful
					it will return true other wise
					the provided float will be un-
					changed and the method will 
					return false.
	************************************************************
	

	********************void setg(const float&);****************
	The setg method will set the gpa equal to the provide
	float.

	Preconditions:	The caller must provide a instialized 
					float
	Postconditions:	The gpa will be set to the provided
					value.
	*************************************************************
	
    ********************public data member*********************** 
										
										
	The SortedLinkedList<T> will protect
	the data from tampering by a user.	
	See the SortedLinkedList.h for 
	available methods and features
										
	SortedLinkedList<Course*> CourseList;

	*************************************************************
*/
protected:

// * * * * protected class method * * * *
	void calcSal();
		// variables associated with protected method
		// this variable will be set to true when
		// either rate or hours is changed
		// and it will be set to false when calcSal
		// is called
		bool doCalc;
// * * * * * * * * * * * * * * * * * * * *
	float hours, rate, salary;

	/*****************************************
		Data inheritaned from Student Class
		
		string first, last
		int ssn
		float gpa
	******************************************/

};

#endif