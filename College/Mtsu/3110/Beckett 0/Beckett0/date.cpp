//FILE: date.cpp
//Author: Timothy Beckett
//Class: CSCI 3110
//Instructor: Seo

# include <iostream>
# include <string>
# include "date.h"
using namespace std;

DateClass::DateClass()
{
	month = "January";

	day = 19;

	year = 2006;
}

void DateClass::printDate()
{
	cout<<"Month: "<<month<<endl;
	cout<<"Day:   "<<day<<endl;
	cout<<"Year:  "<<year<<endl;
}

void DateClass::readDate()
{
	cout<<"What is the  current month?\n";
	cin>>month;
	cout<<"What is the current day?\n";
	cin>>day;
	cout<<"What is the current year?\n";
	cin>>year;
	cout<<"Thank you for the information\n";
}