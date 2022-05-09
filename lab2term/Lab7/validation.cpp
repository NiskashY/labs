#include "validation.h"

double InputA() {
	const std::string& kMessage = "Input a: ";
	std::cout << kMessage;
	double a = 0;
	CheckNum(std::cin, a);
	return a;
}

double InputB(const double& a) {
	const std::string& kMessage = "Input b: ";
	const std::string& kError = "b must be more than a! ReEnter: ";
	bool isError = false;
	double b = 0;

	std::cout << kMessage;
	do {
		CheckNum(std::cin, b);
		isError = IsLess(a, b);
		if (isError) {
			std::cout << kError;
		}
	} while (isError);

	return b;
}

int InputM() {
	const std::string& kMessage = "Input m: ";
	const std::string& kError = "m must be more than 1! ReEnter: ";
	bool isError = false;
	int m = 0;
	// min_m = 2, because if m (or n) <= 1  =>
	// => in FindH(...) the denominator == 0 || (denominator < 0 => h < 0)
	const int min_m = 2; 
	
	std::cout << kMessage;
	do {
		CheckNum(std::cin, m);
		isError = IsLess(min_m, m);
		if (isError) {
			std::cout << kError;
		}
	} while (isError);

	return m;
}

int InputN(const int& m) {
	const std::string& kMessage = "Input n: ";
	const std::string& kError = "n must be not less than m! ReEnter: ";
	bool isError = false;
	int n = 0;

	std::cout << kMessage;
	do {
		CheckNum(std::cin, n);
		isError = IsLess(m, n);
		if (isError) {
			std::cout << kError;
		}
	} while (isError);

	return n;
}
