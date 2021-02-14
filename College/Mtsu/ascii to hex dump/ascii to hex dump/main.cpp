# include <fstream>
# include <iomanip>
# include <iostream>
# include <string>

using namespace std;

int main()
{
	ofstream fout;
	ifstream fin;
	char letter;
	int i = 1;
	
	fout.open("hexdump.txt");
	fin.open("ascii.txt");

	letter = fin.get();

	while(fin)
	{
		if(i == 0)
			fout << endl;

		fout << hex << (int)letter;

		letter = fin.get();

		i = (i + 1) % 10;
	}

	fout.close();
	fin.close();

	return 0;
}