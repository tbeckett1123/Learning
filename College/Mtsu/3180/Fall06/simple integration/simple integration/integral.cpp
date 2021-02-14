// estimate integral of exp(-x^2) on [0,1]
// author: R. Detmer
// date: 10/3/05
// revised: 10/3/06

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int nbrIntervals;
	float sum;
	float x;
	float h;
	
	cout << "How many subintervals of [0,1]? ";
	cin >> nbrIntervals;
	h = 1.0 / nbrIntervals;

	cout << "\nStarting with large terms" << endl << endl;
	sum = 0.0;
	for (int i = 1; i <= nbrIntervals; i++)
	{
		x = i*h;		// right-hand endpoint
		sum += exp(-x*x);
	}
	cout << "Lower sum " << sum*h << endl;

	sum = 0.0;
	for (int i = 0; i < nbrIntervals; i++)
	{
		x = i*h;		// right-hand endpoint
		sum += exp(-x*x);
	}
	cout << "Upper sum " << sum*h << endl;

	cout << "\nStarting with small terms" << endl << endl;
	sum = 0.0;
	for (int i = nbrIntervals; i >= 1; i--)
	{
		x = i*h;		// right-hand endpoint
		sum += exp(-x*x);
	}
	cout << "Lower sum " << sum*h << endl;

	sum = 0.0;
	for (int i = nbrIntervals-1; i >= 0; i--)
	{
		x = i*h;		// right-hand endpoint
		sum += exp(-x*x);
	}
	cout << "Upper sum " << sum*h << endl << endl;

	return 0;
}