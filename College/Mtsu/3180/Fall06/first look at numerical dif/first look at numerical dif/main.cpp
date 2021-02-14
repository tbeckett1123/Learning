// find approximations to f'(x) where f(x) = sin(x)
// author: R. Detmer
// date: 8/28/05

#include <math.h>
#include <iostream>
using namespace std;

int main()
{
	float error;
	float h;
	float x;
	float y;
	int n;

	cout << "x? ";
	cin >> x;
	cout << "number of iterations? ";
	cin >> n;

	h = 1.0;
	for (int i=0; i<n; i++)
	{
		h = 0.25*h;
		y = (sin(x+h) - sin(x))/h;
		error = fabs(cos(x) - y);
		cout << "\niteration " << i+1 << "  h = " << h
			<< "  approximation = " << y << "  error = " << error << endl;
	}
	return 0;
}

