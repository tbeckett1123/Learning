//data restriction	you may only have an odd number of newlines in a line.
//					all hex letters must be lower case.

# include <iostream>
# include <iomanip>
# include <string>
# include <fstream>
# include <ctype.h>

using namespace std;

int main()
{
	ofstream fout("ascii.txt");
	ifstream fin("hexdump.txt");
	int charValue, hexNum2C;
	char hexNum1, hexNum2;
	string line;

	getline(fin, line);

	do
	{

		if(line.size()%2 != 0)	//check for even number of chars and correct accordingly
				line = line + " ";

		for(unsigned int i = 0; i < line.size() - 1; i += 2)
		{
			hexNum1 = line[i];
			hexNum2 = line[i+1];

			while(hexNum1 == 'a' && i < line.size() -1)		//check for newline
			{
				fout << endl;

				hexNum1 = hexNum2;							//process next char
				hexNum2 = line[i+2];
			
				i++; //adjust i accordingly.
			}

			hexNum1 &= 15;					//strip ascii bits from number
			hexNum2C = isalpha(hexNum2);	//check if number > 9
			hexNum2 &= 15;					//strip ascii bits from number

			//calculate ascii char to be printed
			charValue	= (int)hexNum1 * 16						//first number x1 * 16^1
						+ (int)hexNum2;

			if(hexNum2C)
				charValue += 9;									//if number > 9 add bias

			fout << (char)charValue;
			}

		getline(fin, line);

	} while(fin);

	fout.close();
	fin.close();

	return 0;
}