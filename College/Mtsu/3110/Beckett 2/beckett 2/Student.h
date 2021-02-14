/*
Programmer:	Timothy Beckett
File:		Student.h -- Student Class
Class:		CSCI 3110
Instructor:	Dr. Seo
*/
# include "Person.h"
# include "SortedLinkedList.h"

# ifndef STUDENT_H
# define STUDENT_H

struct Course
{
	string	description,	//Course name		optional
							//	and short
							//	description 
			dept;			//Department		required
	int		num,			//Course id number	required
			sect,			//section number	optional
			hours;			//credit hours		optional
	char	grade;			//					required

	void print()
	{
		cout<<dept<<" "<<num<<" "<<grade<<endl;
	}//end print

	void read()
	{
		cout<<"enter the department\n";
		cin>>dept;
		cout<<"enter the course id number\n";
		cin>>num;
		cout<<"enter teh final grade\n";
		cin>>grade;
	}//end read

	//overloaded operator
	bool operator<(const Course& rValue)
	{
		if(dept < rValue.dept  || ((dept == rValue.dept) && (num < rValue.num)))
			return true;

		return false;
	}//end operator <

	//overloaded operator
	bool operator==(const Course& rValue)
	{
		if(dept == rValue.dept && num == rValue.num)
			return true;

		return false;
	}//end operator ==

	const Course& operator=(const Course& rValue)
	{
		description = rValue.description;
		dept = rValue.dept;
		num = rValue.num;
		hours = rValue.hours;
		grade = rValue.grade;

		return rValue;
	}//end operator=

	//constructor
	Course()
	{	
		description = "empty";
		dept = "empty";
		num	 = 0;
		grade = 'E';
		hours = 0;
		sect = 0;
	}//end Course constructor
};

class Student: public Person
{

// * * * * friend functions * * * *

	friend ostream& operator<<(ostream&, Student&);
	friend istream& operator>>(istream&, Student&);

public:
// * * * * constructors * * * * 

	//defualt constructor
	Student();

	//copy constructor
	Student(Student&);

	//initialize constructor
	Student(string, string, int, float, SortedLinkedList<Course*>); 

// * * * * class methods * * * *
	
	/*
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
	*/
	bool getg(float&);

	/*
	The setg method will set the gpa equal to the provide
	float.

	Preconditions:	The caller must provide a instialized 
					float
	Postconditions:	The gpa will be set to the provided
					value.
	*/
	void setg(const float&);

// * * * * public data member * * * * ** 
										
	/*									
	The SortedLinkedList<T> will protect
	the data from tampering by a user.	
	See the SortedLinkedList.h for 
	available methods and features
	*/									
	SortedLinkedList<Course*> CourseList;


// * * * * * * * * * * * * * * * * * * * 

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
	Postconditions:	returns the char 's'
	*/
	virtual char id();

// * * * * Overloaded Operators * * * *

	bool operator<(const Student&);

	bool operator==(const Student&);

	Student& operator=(Student&);

// * * * * Available from Person Class * * * * 
/*
	************** bool getf(string &); ************************
		This get method will retreive the Persons first name
	
	Precondition:	The user must provide a string variable
					for the first name to be stored in.
	Postconditions:	The first name of the Person will be 
					stored in the the provide varialbe if
					it has be set by the user
					if the operation is successful the 
					method will return true otherwise it 
					will return false
	************************************************************
	
	****************** bool getl(string &); ********************
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
	************************************************************

	**********************bool gets(int &);*********************	
	This get method will retreive the Persons ssn

	Precondition:	The user must provide an int variable
					for the ssn to be stored in.
	Postconditions:	The ssn of the Person will be 
					stored in the the provide varialbe if
					it has be set by the user
					if the operation is successful the 
					method will return true otherwise it 
					will return false
	************************************************************

	********************void setf(const string &);**************
	This set function will set the Persons first name

	Preconditions:	The user must provide a string
					with the Persons name in it.
	Postconditions:	The object string variable first will be 
					set to the provided string.
					This method has no return value
	************************************************************
	
	********************void setl(const string &);**************
	This set function will wet the Persons last name

	Preconditions:	The user must provide a string
					with the Persons last name in it	
	Postconditions:	The object string variable last will be set
					to the provided string
					This method has no return value
	************************************************************
	
	*******************void sets(const int &);******************
	This set method will set the Persons ssn

	Preconditions:	The user must provide an int
	Postconditions:	The object int ssn will be set to
					the provided int
					This method has no return value
	************************************************************
	
	********************bool operator==(const Person &);********
	This overload operator == will compare to
	Person objects to determine if first and
	last names are equal.

	preconditions:	The user must provide an 
					Person object
	postconditions:	this method will return true
					if the names are the same
					otherwise it will return false
	************************************************************
		
	*********const Person& operator=(const Person &);**********
	This overloaded operator = will assign the values
	of one Person object to the new one.

	Precoditions:	The user must provide an Person object
					to copy.
	Postcoditions:	this object will be a copy of the provided
					object.
					This method returns a copy of the provided
					object.
	************************************************************
	
	***************bool operator<(Person &) const;**************
	This method will determine if the L value Person is less
	than the R value Person

	Preconditions:	The calling method must proved a Person obj
	Postconditions:	if this obj is less than the provided obj
					it will return true.
					if this obj is greater than the provided obj
					it will return false.
	************************************************************
*/

protected:
	
	float gpa;

	/*****************************************
		Data inheritaned from Person Class
		
		string first, last
		int ssn
	******************************************/

};

# endif