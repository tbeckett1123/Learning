/*
Programmer:		Timothy Beckett
Class:			CSCI 3110
Instructor:		Dr. Seo
File:			video.h
*/
# include <iostream>
# include <iomanip>
# include <fstream>
# include <string>

using namespace std;

# ifndef VIDEO_H
# define VIDEO_H

class Video
{
	friend ofstream& operator<<(ofstream&, const Video&);
	friend ostream& operator<<(ostream&, const Video&); 
	friend istream& operator>>(istream&, Video&); 
	
public:
	Video();								//Default Constructor
	Video(const Video&);					//Copy Constructor

	void operator++();						//Increment copies available
	void operator--();						//Decrement copies available
	void set_available(const int&);			//set the number of copies
											//available. This may only be
											//done once.
	int return_available();					//return the number of available
											//copies
	bool operator<(const Video&);			
	bool operator>(const Video&);
	bool operator==(const Video&);
	bool operator!=(const Video&);
	const Video& operator=(const Video&);

	string	title,
			stars,
			director,
			producer,
			production_company;
private:
	int		available;
	bool	set;
};

# endif