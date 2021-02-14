/*
Programmer:	Timothy Beckett
File:		impStudent.h -- Student Class
Class:		CSCI 3110
Instructor:	Dr. Seo
*/

# include "Student.h"
# include "impSortedLinkedList.cpp"

// * * * * Constructors * * * *

//defualt constructor
Student::Student()
{
	gpa = 0.0;
}//end defualt constructor

//copy constructor
Student::Student(Student& org): Person(org.first, org.last, org.ssn)
{
	gpa = org.gpa;
	Course *buf;

	for(int index = 0; index < org.CourseList.Size(); index++)
	{
		org.CourseList.get(buf, index);
		CourseList.ins(buf);
	}//end for
}//end copy constructor

//initialize constructor
Student::Student(string iLast, string iFirst, int iSsn,
				 SortedLinkedList<Course*> iCourseList)
				 : Person(iFirst, iLast, iSsn)
{
	Course *buf;

	for(int i = 0; i < iCourseList.Size(); i++)
	{
		iCourseList.get(buf, i);
		CourseList.ins(buf);
	}//end for

	calcGpa();

}// end initialize constructor

// * * * * friend functions * * * * 

ostream& operator<<(ostream& out, Student & printer)
{
	Course *cPrint;
	int i;

	out <<left<<endl
		<<printer.last<<endl
		<<printer.first<<endl
		<<printer.ssn<<endl
		<<fixed<<setprecision(3)<<printer.gpa<<endl;

	for(i = 0; i < printer.CourseList.Size(); i++)
	{
		printer.CourseList.get(cPrint, i);
		
		out <<cPrint->dept<<" "<<cPrint->num<<" "<<cPrint->grade<<" "<<endl;
	}//end for

	return out;
}//end operator <<

istream& operator>>(istream& in, Student& geter)
{
	in  >>geter.last
		>>geter.first
		>>geter.ssn;
	
	//Enter 'quit' to stop entering courses
	Course *c;
	c = new Course();	
	for(c->dept = "go"; c->dept != "quit"; )
	{
		
		in>>c->dept;

		if(c->dept != "quit")
		{
			//enter the id number
			in>>c->num;
			//enter the final grade
			in>>c->grade;
			//enter hours hours earned/atempted
			in>>c->hours;
			
			geter.CourseList.ins(c);
		}//end if

	}//end for

	return in;
}//end operator >>

// * * * * class methods * * * *

float Student::Gpa()
{
	calcGpa();

	return gpa;
}//end getg

void Student::calcGpa()
{
	float tHours = 0.0, tGradePoints = 0.0;
	Course *course;

	if(CourseList.Size() > 0)
	{
		for(int i = 0; i < CourseList.Size(); ++i)
		{
			CourseList.get(course, i);		

			switch(course->grade)
			{
			case 'A':
				tHours += course->hours;
				tGradePoints += 4.0*course->hours;
				break;
			case 'B':
				tHours += course->hours;
				tGradePoints += 3.0*course->hours;
				break;
			case 'C':
				tHours += course->hours;
				tGradePoints += 2.0*course->hours;
				break;
			case 'D':
				tHours += course->hours;
				tGradePoints += 1.0*course->hours;
				break;
			case 'F':
				tHours += course->hours;
				tGradePoints += 0.0*course->hours;
		
			//Grades marked E mean that the student is currently
			//enrolled and the course is to be excluded
		
			};//end switch
		
		}//end for

		gpa = tGradePoints / tHours;

	}//end if
	
}//end calcGpa

// * * * * virtual methods * * * * 

void Student::display()
{
	Gpa();		//calculate gpa
				//just in case :-)

	 cout<<left
		 <<setw(9)<<last.substr(0, 8)
		 <<setw(9)<<first.substr(0, 8)
		 <<setw(10)<<ssn
		 <<setw(10)<<fixed<<setprecision(3)<<gpa
		 <<right;
}//end display

void Student::read()
{
	 cout<<"Enter the first name: ";
	 cin>>first;
	 cout<<"Enter the last name: ";
	 cin>>last;
	 cout<<"Enter the Social Security Number: ";
	 cin>>ssn;
	 
	cout<<"To stop enter courses\n"
		<<"Enter quit for the dept\n"
		<<"Enter 1111 for the id number\n"
		<<"Enter E for the Grade\n"
		<<"Enter 0 for the hours\n";

	Course *c;
	c = new Course();	
	for(c->dept = "go"; c->dept != "quit"; )
	{
		c->read();

		if(c->dept != "quit")
		{
			CourseList.ins(c);
		}//end if
	}//end for


}//end read

char Student::id()
{return 's';}

// * * * * Overloaded Operators * * * * 

bool Student::operator <(const Student& rValue)
{
	if(last < rValue.last || last == rValue.last && first < rValue.first)
		return true;

	return false;
}//end operator <

bool Student::operator==(const Student& rValue)
{
	if(last == rValue.last && first == rValue.first)
		return true;

	return false;
}//end operator ==

 Student& Student::operator=(Student& rValue)
{
	last = rValue.last;
	first = rValue.first;
	ssn = rValue.ssn;
	gpa = rValue.gpa;

	Course *buf;

	for(int index = 0; index < rValue.CourseList.Size(); index++)
	{
		rValue.CourseList.get(buf, index);
		CourseList.ins(buf);
	}//end for
	
	return rValue;
}//end operator =