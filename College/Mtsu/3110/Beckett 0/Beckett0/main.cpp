//FILE: date.cpp
//Author: Timothy Beckett
//Class: CSCI 3110
//Instructor: Seo


# include <iostream>
# include <string>
# include "date.h"
using namespace std;

int main()
{
	DateClass today;
	today.readDate();
	today.printDate();
	return 0;
}