//FILE: date.h
//Author: Timothy Beckett
//Class: CSCI 3110
//Instructor: Seo

# include <iostream>
# include <string>
# ifndef DATE_H
# define DATE_H
using namespace std;
class DateClass
{
public: DateClass();
		void readDate();
		void printDate();

private: string month;
		 int day, year;
};

# endif