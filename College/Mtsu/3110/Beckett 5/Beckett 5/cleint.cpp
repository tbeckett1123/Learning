/*
Programmer:		Timothy Beckett
Class:			CSCI 3110
Instructor:		Dr. Seo
File:			cleint.cpp
Objective:		This program reads in a list of Video Records
				and Customer Records from file (customers.dat
				and movies2.dat), and stows them in to a RBT<U>
				It has the following functions: Rent a video,
				Return a video, create a list of videos owned
				by the store, shows the detals of a particular
				video, check if a particular video is in the store,
				and maintin a customer database.
*/
# include "bst.h"
# include "impBST.cpp"
# include "video.h"
# include "Customer.h"
# include "table.h"
# include <iomanip>
# include <ctype.h>

using namespace std;

template <typename R>
void Read(const string&, BST<R>&);
void Rent(BST<Video>&, BST<Customer>&);
void Return(BST<Video>&);
void Show(BST<Video>&);
void Members(BST<Customer>&);



int main()
{
	BST<Video> vList;
	BST<Customer> cList;
	char choice;

	Read("movies.dat", vList);
	Read("customers.dat", cList);

	do
	{
		system("cls");

		cout<<left
			<<tl_c<<setfill(hr_l)<<setw(33)<<hr_l<<setfill(' ')<<tr_c<<endl

			<<setw(3)<<vr_l<<setw(31)<<"Video Rental Managment System"<<vr_l<<endl
			
			<<vl_t<<setfill(hr_l)<<setw(4)<<hr_l<<tt_t<<setw(28)<<hr_l<<setfill(' ')<<vr_t<<endl
			
			<<setw(3)<<vr_l<<setw(2)<<'a'<<setw(3)<<vr_l<<setw(26)<<"Rent a video"			<<vr_l<<endl
			<<setw(3)<<vr_l<<setw(2)<<'b'<<setw(3)<<vr_l<<setw(26)<<"Return a video"		<<vr_l<<endl
			<<setw(3)<<vr_l<<setw(2)<<'c'<<setw(3)<<vr_l<<setw(26)<<"List all video"		<<vr_l<<endl
			<<setw(3)<<vr_l<<setw(2)<<'d'<<setw(3)<<vr_l<<setw(26)<<"Show video details"	<<vr_l<<endl
			<<setw(3)<<vr_l<<setw(2)<<'e'<<setw(3)<<vr_l<<setw(26)<<"Add new member"		<<vr_l<<endl
			<<setw(3)<<vr_l<<setw(2)<<'f'<<setw(3)<<vr_l<<setw(26)<<"Shutdown System"		<<vr_l<<endl
			
			<<bl_c<<setfill(hr_l)<<setw(4)<<hr_l<<bt_t<<setw(28)<<hr_l<<setfill(' ')<<br_c<<endl
			
			<<"Please make a selection: ";
		
		cin>>choice;

		choice = tolower(choice);

		switch(choice)
		{
		case 'a': Rent(vList, cList);	break;
		case 'b': Return(vList);		break;
		case 'c': system("cls");
				  vList.Inorder(); 
				  system("pause");		break;
		case 'd': Show(vList);			break;
		case 'e': Members(cList);		break;
		default:	cout<<"Thank You\n";
		};	
	}while(choice != 'f');

	return 0;
}

template <typename R>
void Read(const string& file, BST<R>& list)
//this generic read fucntion will read in data of Type R and
//insert it into a RBT<R>.
//Preconditions:	user must provide a string which contains
//					the name of the file to be read from
//					user must provide a RBT<R> to store the 
//					records in.
//					the data type R must have an overloaded
//					>> operator
//Postconditions:	The tree will be populated with the records
//					from the file.
{
	R data;
	fstream fin;

	fin.open(file.c_str());

	if(!fin)
		return;
	
	fin>>data;

	while(!fin.eof())
	{
		list.Ins(data);
		fin>>data;
	}

	fin.close();
}


void Rent(BST<Video>& vList, BST<Customer>& cList)
//This function will get the name of the movie to be rented
//and the account number of the user member number.
//Preconditions:	user must provide a RBT<video> and a 
//					RBT<Customer>
//Postconditions:	if the video is found and the member
//					has a valid account number (not suspended)
//					the video will be add to the member
//					list and the available count will be 
//					decremented by one.
{
	system("cls");
	Video vid;
	Customer account;
	
	cout<<"Enter the video title: ";
	cin.ignore();
	getline(cin, vid.title, '\n');

	Video& copy = vList.Ret(vid);

	cout<<"Enter the member acount number: ";
	cin>>account.acount_number;

	Customer& member = cList.Ret(account);

	int i, j;

	for(i = 0; i < MAX_COUNT; ++i)		//checking to see if
		if(member.list[i] == "empty")	//member may rent another video
		{
			j = i;
			i = MAX_COUNT;
		}

	if(j < MAX_COUNT)
	{
		member.list[j] = copy.title;
		copy--;
	}
	else
	{
		cout<<"members aren't allowed to checkout more than 10 videos\n";
				
	system("pause");
	}
	
}

void Return(BST<Video>& vList)
//This function prompt the user for the title of the returned video
//and will increament available movie count
//Preconditions:	user must provide a BRT<Video>
//Postconditions:	the count of the video will be increamented
{
	system("cls");
	Video vid;
	cout<<"Enter the title of the video: ";
	cin.ignore();
	getline(cin, vid.title, '\n');
	
	Video& copy = vList.Ret(vid);
	copy++;
}

void Show(BST<Video>& vList)
//This fucntion will prompt the user for the title of
//the video desired and will display the details of the
//video.
//Preconditions:	user must provide a RBT<Video>
//Postconditions:	n/a
{
	system("cls");
	Video vid;
	cout<<"Enter the title of the video: ";
	cin.ignore();
	getline(cin, vid.title, '\n');

	Video& copy = vList.Ret(vid);

	cout<<left
		<<setfill(hr_l)
		<<setw(11)<<tl_c<<setw(40)<<tt_t<<setfill(' ')<<tr_c<<endl
		<<setw(2)<<vr_l<<setw(9)<<"Title"	<<setw(3)<<vr_l<<setw(37)<<copy.title.substr(0, 35)				<<vr_l<<endl
		<<setw(2)<<vr_l<<setw(9)<<"Stars"	<<setw(3)<<vr_l<<setw(37)<<copy.stars.substr(0, 35)				<<vr_l<<endl
		<<setw(2)<<vr_l<<setw(9)<<"Dir"		<<setw(3)<<vr_l<<setw(37)<<copy.director.substr(0, 35)			<<vr_l<<endl
		<<setw(2)<<vr_l<<setw(9)<<"Producer"<<setw(3)<<vr_l<<setw(37)<<copy.producer.substr(0, 35)			<<vr_l<<endl
		<<setw(2)<<vr_l<<setw(9)<<"Company"	<<setw(3)<<vr_l<<setw(37)<<copy.production_company.substr(0, 35)<<vr_l<<endl
		<<setw(2)<<vr_l<<setw(9)<<"copies"	<<setw(3)<<vr_l<<setw(37)<<copy.return_available()<<vr_l<<endl
		<<setfill(hr_l)
		<<setw(11)<<bl_c<<setw(40)<<bt_t<<setfill(' ')<<br_c<<endl;
	system("pause");
}

void Members(BST<Customer>& cList)
//This function will add a new customer
//to the customber list.
//Preconditions:	user must provide a RBT<Customber>
//Postconditions:	the new customer will be added to
//					the RBT
{
	system("cls");
	Customer c;

	cout<<"Enter the account number: ";
	cin>>c.acount_number;
	cout<<"Enter the First name: ";
	cin>>c.first;
	cout<<"Enter the Last name: ";
	cin>>c.last;

	cList.Ins(c);
}