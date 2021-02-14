# include <iostream>
# include "calendar.h"

int main()
{
	calendar c;
	int i;
	do
	{

	cin >> i;
	c.ShowMonth(i);
	}while(i);

	return 0;
}