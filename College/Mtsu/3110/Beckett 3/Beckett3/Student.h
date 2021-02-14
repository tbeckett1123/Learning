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
	string	dept;			//Department		
	int		num;			//Course id number	
	float	hours;			//credit hours		
	char	grade;			//final grade					

	void print()
	{
		cout<<dept<<" "<<num<<" "<<grade<<" "<<fixed<<setprecision(1)<<hours<<endl;
	}//end print

	void read()
	{
		cout<<"enter the department\n";
		cin>>dept;
		cout<<"enter the course id number\n";
		cin>>num;
		cout<<"enter the number of credit hours\n";
		cin>>hours;
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
		dept = rValue.dept;
		num = rValue.num;
		hours = rValue.hours;
		grade = rValue.grade;

		return rValue;
	}//end operator=

	//constructor
	Course()
	{	
		dept = "empty";
		num	 = 0;
		grade = 'E';
		hours = 0;		
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
	Student(string, string, int, SortedLinkedList<Course*>); 

// * * * * class methods * * * *
	
	/*
	This method returns the gpa to the user.
	It will calculate the gpa if needed.

	Preconditions:	None
	Postconditions:	The methdo will return the gpa.
					If the gpa has not been assigned
					a -1.0 will be returned.
	*/
	float Gpa();
										

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

// * * * * data members * * * * 

	//This is a list of all classes the student
	//has taken.  Courses they're currently en-
	//rolled in may be included also; use the 
	//letter E for the grade of classes that the
	//student is currently enrolled in; all other
	//letter grades should be a capital letter (A
	//B, C, D, F, E)
	//This list is use to calculate the gpa
	SortedLinkedList<Course*> CourseList;

	/*****************************************
		Data inheritaned from Person Class
		
		string	first,	//First Name
				last	//Last name
		int		ssn		//Social Security Number
	******************************************/

protected:

	void calcGpa();
	
	float gpa;
};

# endif