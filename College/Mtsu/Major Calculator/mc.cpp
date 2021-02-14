# include <iostream>
# include <iomanip>
# include <fstream>
# include <cstring>
# define MJ 18
# define MR 5
# define GE 13

using namespace std;

struct course
{
	char dept[5];
	int number,
		finished,
		hours,
		mult;
};
/******************************************
GEN ED = 4
MINOR = 1
MAJOR = 2
THEREFORE IF THE NUMBER FOR MULT IS 5 THE 
CLASS IS IN BOTH THE MINOR AND IN GEN ED
*******************************************/
void writer(course major[], course minor[], course gened[]);
int reader(course major[], course minor[], course gened[]);
void printArray(const course TEMP[]/*major, minor, gened*/, const int & SIZE/*MJ, MR, GE*/);
void mkgraph(course major[], course minor[], course gened[]);
void printDatabase();

int main()
{
	course major[MJ], gened[GE], minor[MR];
	char select;
	int stopStatus = 0;
	stopStatus = reader(major, minor, gened);

	if(stopStatus) return stopStatus;
	
	do
	{
	    cout<<"0) print database\n"
			<<"1) print statistics & remaining class list\n"
		    <<"2) edit database\n"
	    	<<"3) quit\n";
	   cin>>select;
	
	   switch(select)
	   {
	    case '2': writer(major, minor, gened);
		     	  break;
		case '1': cout<<"You have completed the following:\n";
				  mkgraph(major, minor, gened);
			      cout<<"Your lack the following from your major:\n";
			      printArray(major, MJ);
				  system("pause");
				  cout<<"Your lack the following from your minor:\n";
				  printArray(minor, MR);
				  system("pause");
				  cout<<"Your lack the following from your Gen Ed:\n";
			      printArray(gened, GE);
				  system("pause");
				  break;
		case '0': printDatabase(); 
	   };
	}
	while(select != '3');
	return stopStatus;
}

int reader(course major[], course minor[], course gened[])
{
	ifstream fin;
	course buffer;
	int mji, mri, gei;
	
	mji = mri = gei = 0;

	fin.open("trans.txt");

	if(!fin)
	{
		cerr<<"<-- The Transcript is missing -->\n";
		return 1;
	}

	fin	>>buffer.dept
		>>buffer.number
		>>buffer.finished
		>>buffer.hours
		>>buffer.mult;
	
	while(fin)
	{
		if(~buffer.mult%2)
		{
			switch(buffer.mult)
			{
			case 6: major[mji] = buffer;
					mji++;
			case 4: gened[gei] = buffer;
					gei++;
					break;
			default:major[mji] = buffer;
					mji++;
			};
		}
		else
		{
			switch(buffer.mult)
			{
			case 5: gened[gei] = buffer;
					minor[mri] = buffer;
					gei++;
					mri++;
					break;
			case 7:	gened[gei] = buffer;
					gei++;
			case 3: major[mji] = buffer;
					mji++;
			default:minor[mri] = buffer;
					mri++;
			};		
		}

		if(mri > MR || mji > MJ || gei > GE) //if any of the arrays are
		{									 //full prematurely
			cerr<<"<-- input overflow -->\n";//shutdown program
			cerr<<"mji = "<<mji<<endl
				<<"mri = "<<mri<<endl
				<<"gei = "<<gei<<endl;
			fin.close();
			return 2;
		}

		fin	>>buffer.dept
			>>buffer.number
			>>buffer.finished
			>>buffer.hours
			>>buffer.mult;
	}
	fin.close();
	return 0;
}

void writer(course major[], course minor[], course gened[])
{
	int number, q = 0;
	char dept[5];
	ifstream fin;
	ofstream fout;
	course w[MJ+MR+GE];

	fin.open("trans.txt");//reading in database for editing
	if(!fin)
		return;

	fin >>w[q].dept
		>>w[q].number
		>>w[q].finished
		>>w[q].hours
		>>w[q].mult;

	while(fin)
	{
		q++;
		fin >>w[q].dept
		    >>w[q].number
		    >>w[q].finished
		    >>w[q].hours
		    >>w[q].mult;
	}
	fin.close(); //done

	cout<<"which class have you completed\n"  //getting change from user
		<<"dept must be in all caps\n"
		<<"ex: MATH 3110\n";
	cin>>dept>>number;

	for(int i = 0; i < q; i++)  //finding record and changing it
	{
		if(w[i].number == number)
		{		
			if(0 == strcmp(w[i].dept, dept))
			{
				w[i].finished = 1;
				i = q;
			}
		}
	}

	fout.open("trans.txt");

	for(int j = 0; j < q; j++)//re-writing database
	{
		fout<<w[j].dept<<" "
			<<w[j].number<<" "
			<<w[j].finished<<" "
			<<w[j].hours<<" "
			<<w[j].mult<<" "<<endl;
	}
	fout.close();
	//re-load database
	reader(major, minor, gened);
}

void printArray(const course TEMP[], const int& SIZE)
{   
	cout<<"# -- means that items appears in more than one list"<<endl;
	cout<<"DEPT NUMBER CREDITS\n"
		<<setfill('-')<<setw(20)<<"-\n"<<setfill(' ');
	char last;
	for(int i = 0; i < SIZE; i++)
	{	
		(TEMP[i].mult == 1 || TEMP[i].mult == 2 || TEMP[i].mult == 4)? last = ' ' : last = '#';
		if(TEMP[i].finished == 0) cout<<TEMP[i].dept<<setw(7)<<TEMP[i].number<<setw(8)<<TEMP[i].hours<<" "<<last<<endl;
	}
}

void mkgraph(course major[], course minor[], course gened[])
{
	int total = (MJ + MR + GE),
		tally, mjtally, mrtally, getally, 
		tpercent, mjpercent, mrpercent, gepercent;
	float percent;

	tally = mjtally = mrtally = getally = 0;

	for(int i = 0; i < MJ; i++)
	{
		if(major[i].finished == 1){mjtally++; tally++;}
	}
	for(int j = 0; j < MR; j++)
	{
		if(minor[j].finished == 1){mrtally++; tally++;}
	}
	for(int k = 0; k < GE; k++)
	{
		if(gened[k].finished == 1){getally++; tally++;}
	}
	percent = (float)tally/(float)total;
	percent *= 100.0;
	tpercent = (int)percent;
	percent = (float)mjtally/(float)MJ;
	percent *= 100.0;
	mjpercent = (int)percent;
	percent = (float)mrtally/(float)MR;
	percent *= 100.0;
	mrpercent = (int)percent;
	percent = (float)getally/(float)GE;
	percent *= 100.0;
	gepercent = (int)percent;

	cout<<setw(10)<<"Total: "<<setw(5)<<tpercent<<"%"<<"  |";
		for(int i = 0; i < tpercent/5; i++)
			cout<<"*";
			cout<<setw(21-tpercent/5)<<"|"<<endl;
	cout<<setw(10)<<"Major: "<<setw(5)<<mjpercent<<"%"<<"  |";
		for(int j = 0; j < mjpercent/5; j++)
			cout<<"*";
			cout<<setw(21-mjpercent/5)<<"|"<<endl;
	cout<<setw(10)<<"Minor: "<<setw(5)<<mrpercent<<"%"<<"  |";
		for(int i = 0; i < mrpercent/5; i++)
			cout<<"*";
			cout<<setw(21-mrpercent/5)<<"|"<<endl;
	cout<<setw(10)<<"Gen Ed: "<<setw(5)<<gepercent<<"%"<<"  |";
		for(int i = 0; i < gepercent/5; i++)
			cout<<"*";
			cout<<setw(21-gepercent/5)<<"|"<<endl;
	system("pause");
}

void printDatabase()
{
	ifstream fin;
	course w;
		cout<<"DEPT NUMBER CREDITS FINISHED\n"
		<<setfill('-')<<setw(30)<<"-\n"<<setfill(' ');
	
	fin.open("trans.txt");

	fin >>w.dept
	    >>w.number
	    >>w.finished
	    >>w.hours
	    >>w.mult;

	while(fin)
	{
		cout<<w.dept<<setw(7)<<w.number<<setw(7)<<w.hours<<setw(9)<<w.finished<<endl;

		fin >>w.dept
		    >>w.number
		    >>w.finished
		    >>w.hours
		    >>w.mult;
	}
	fin.close();
}