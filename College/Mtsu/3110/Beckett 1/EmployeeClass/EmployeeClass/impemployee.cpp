/*
Programmer:	Timothy Beckett
Class:		CSCI 3110
Instructor:	Dr. Seo
*/
# include "Employee.h"

//default constructor
Employee::Employee()
{
	first = last = "nobody";
	ssn = 0;
	salary = -1.0;
}//end default

//copy constructor
Employee::Employee(const Employee & org)
{
	first = org.first;
	last = org.last;
	ssn = org.ssn;
	salary = org.salary;
}//end copier

//initialize constructor
Employee::Employee(const string& fn, const string& ln, const int& ss, const double& sal)
{
	first = fn;
	last = ln;
	ssn = ss;
	salary = sal;
}//end intializer

//get the first name
bool Employee::get(string& ptrFirst)
{
	if(first == "nobody")
		return false;
	
	ptrFirst = first;

	return true;
}//end get first name

//get the last name
//use defined word LAST to select method
bool Employee::get(string & ptrLast, const char & check)
{
	if(last == "nobody")
		return false;

	ptrLast = last;

	return true;
}//end get last name

//get the ssn
bool Employee::get(int & ptrSSN)
{
	if(ssn == 0)
		return false;

	ptrSSN = ssn;

	return true;
}//end get ssn

//get the salary
bool Employee::get(double & ptrSalary)
{
	if(salary < 0)
		return false;

	ptrSalary = salary;

	return true;
}//end get salary

//set first name
void Employee::set(const string & newFirst)
{
	first = newFirst;
}//end set first name

//set last name
//use defined word LAST
void Employee::set(const string & newLast, const char & check)
{
	last = newLast;
}//end set last name

//set ssn
void Employee::set(const int & newSSN)
{
	ssn = newSSN;
}//end set ssn

//set Salary
void Employee::set(const double & newSalary)
{
	salary = newSalary;
}//end set salary

//overloaded == operator will return true if the names are the same
bool Employee::operator ==(const Employee & rValue)
{
	if(first == rValue.first && last == rValue.last)
		return true;

	return false;
}//end operator ==

//overload = operator will copy the the rValue into the lValue object
 const Employee& Employee::operator=(const Employee & rValue)
{
	first = rValue.first;
	last = rValue.last;
	ssn = rValue.ssn;
	salary = rValue.salary;

	return rValue;
}//end operator =

// friend functions
//overloaded operators << and >>
ostream& operator<<(ostream& out, const Employee& printer)
{
	out	<<left
		<<setw(10)
		<<printer.first.substr(0, 9)
		<<setw(10)
		<<printer.last.substr(0, 9)
		<<setw(10)
		<<printer.ssn
		<<setw(10)
		<<setprecision(2)<<fixed
		<<printer.salary
		<<endl<<right;
	return out;
}//end operator <<

istream& operator>>(istream& in, Employee& writer)
{
	in >>writer.first;
	in >>writer.last;
	in >>writer.ssn;
	in >>writer.salary;

	return in;
}//end operator >>