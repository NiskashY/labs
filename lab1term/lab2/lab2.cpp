
#include <iostream>

using namespace std;

int main()
{
	double a, b, x, z, function;
	string choose_of_function;
	bool answer = true;
	cout << "Input a: ";
	cin >> a;
	cout << "Input b: ";
	cin >> b;
	cout << "Input z: ";
	cin >> z;

	z < 1 ? x = z * z * z + 0.2 : x = z + log(z);

	cout << "Choose the function u will use in the programm:\n for f(x) = 2x input 1\n for f(x) = x^2 input 2\n for f(x) = x/3 input 3\n";
	while (answer) {
		cin >> choose_of_function;
		if (choose_of_function == "1") {
			function = 2 * x; answer = false;
		}
		else if (choose_of_function == "2") {
			function = x * x; answer = false;
		}
		else if (choose_of_function =="3") {
			function = x / 3.; answer = false;
		}
		else cout << "repeat your input, but now correct pls\n";
	}

	cout << "Result = " << 2 * a * pow(cos(x * x), 3) + sin(x * x * x) * sin(x * x * x) - b * function;
}