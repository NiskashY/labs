#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	double x, y, z, product1, product2;

	// Entering variables
	cout << "Enter x:\n";
	cin >> x;
	cout << "Enter y:\n";
	cin >> y;
	cout << "Enter z:\n";
	cin >> z;

	// Calculating product1 & product2
	product1 = pow(fabs(cos(x) - cos(y)), 1 + 2 * sin(y) * sin(y));
	product2 = 1 + z + z * z / 2 + z * z * z / 3 + z * z * z * z / 4;

	// Calculating answer
	cout << "Result = " << product1 * product2;
}