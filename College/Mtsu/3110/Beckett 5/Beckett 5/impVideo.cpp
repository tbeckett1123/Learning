/*
Programmer:		Timothy Beckett
Class:			CSCI 3110
Instructor:		Dr. Seo
File:			video.cpp
*/
# include "video.h"
# ifndef IMPVIDEO_CPP
# define IMPVIDEO_CPP
/********** Constructors ***************************/
Video::Video()
{
	title = director = producer = production_company = "Empty";
	
	stars = "Empty";
	
	set = false;
	available = 0;
}

Video::Video(const Video &org)
{
	title = org.title;
	
	stars = org.stars;
	
	producer = org.producer;

	director = org.director;

	production_company = org.production_company;

	available = org.available;

	set = true;
}

/************** Operators *****************/
void Video::operator ++()
{available++;}

void Video::operator --()
{
	(available < 1) ? available = 0 : available--;
}

bool Video::operator >(const Video &r_value)
{return (title > r_value.title);}

bool Video::operator <(const Video &r_value)
{return (title < r_value.title);}

bool Video::operator ==(const Video &r_value)
{return (title == r_value.title);}

bool Video::operator !=(const Video &r_value)
{return (title != r_value.title);}

const Video& Video::operator =(const Video &r_value)
{
	title = r_value.title;
	producer = r_value.producer;
	director = r_value.director;
	production_company = r_value.production_company;
	available = r_value.available;
	set = r_value.set;
	stars = r_value.stars;

	return r_value;
}

/************* class methods ****************/
void Video::set_available(const int & s)
{
	if(!set)
	{
		set = true;
		available = s;
		return;
	}

	cout<<"The number available has already been set\n";
	system("pause");
}

int Video::return_available()
{return available;}

/*********** friend functions *****************/
ostream& operator<<(ostream& out, const Video& printer)
{
	out	<<left
		<<setw(17)<<printer.title.substr(0, 15)
		<<setw(17)<<printer.stars.substr(0, 15)
		<<setw(17)<<printer.director.substr(0, 15)
		<<setw(17)<<printer.production_company.substr(0, 15)
		<<setw(17)<<printer.available;
	
	return out;
}


istream& operator>>(istream& in, Video& writer)
{
	getline(in, writer.title, '\n');
	getline(in,writer.stars, '\n');
	getline(in,writer.director, '\n');
	getline(in,writer.producer, '\n');
	getline(in,writer.production_company, '\n');
	in>>writer.available;
	in.ignore();

	return in;
}

# endif