/*
Programmer:		Timothy Beckett
Class:			CSCI 3110
Instructor:		Dr. Seo
File:			impCounter.cpp
*/

# include "Counter.h"

/*********** Friend Function ***************/

ostream& operator<<(ostream& out, const Counter& printer)
{
	out<<printer.count;

	return out;
}//end operator <<

/************** Constructors ****************/

//default constructor
Counter::Counter()
{
	count = reset = 0;
}//end default constructor

//initialize constructor
Counter::Counter(const int initVar)
{
	count = reset = initVar;
}//end initialize constructor

//copy constructor
Counter::Counter(const Counter & org)
{
	count = org.count;
	reset = org.reset;
}//end copy constructor

/********** Overloaded Comparison Operators ***********/

//operator overloads for Counters

bool Counter::operator<(const Counter& rValue) const
{
	return (count < rValue.count);
}//end operator <

bool Counter::operator>(const Counter& rValue) const
{
	return (count > rValue.count);
}//end operator >

bool Counter::operator==(const Counter& rValue) const
{
	return (count == rValue.count);
}//end operator ==

//operator overloads for ints

bool Counter::operator<(const int & rValue) const
{
	return (count < rValue);
}//end operator <

bool Counter::operator>(const int & rValue) const
{
	return (count > rValue);
}//end operator >

bool Counter::operator==(const int & rValue) const
{
	return (count == rValue);
}//end operator ==

/************ Overloaded Increment Operator *************/

void Counter::operator ++()
{
	count++;
}//end operator ++

/************* Class Methods ****************/

int Counter::Return() const
{
	return count;
}//end Return

void Counter::Reset()
{
	count = reset;
}//end Reset