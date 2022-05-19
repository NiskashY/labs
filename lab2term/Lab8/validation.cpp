#include "validation.h"

double InputA() {
	const std::string& kMessage = "Input a: ";
	const std::string& kError = "a must be not equal to zero! ReEnter: ";
	std::cout << kMessage;
	double a = 0;

	do {
		CheckNum(std::cin, a);
		if (!a) {
			std::cout << kError;
		}
	} while (!a);

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

int InputN() {
	const std::string& kMessage = "Input n: ";
	const std::string& kError = "n must be not less than 1! ReEnter: ";
	bool isError = false;
	int n = 0;
	int min_n = 1;

	std::cout << kMessage;
	do {
		CheckNum(std::cin, n);
		isError = IsLess(min_n, n);
		if (isError) {
			std::cout << kError;
		}
	} while (isError);

	return n;
}

double InputEpsilon() { // ia tyt xotel postavit granici ot 1e-6, do 0.5 :|
	const std::string& kMessage = "Input epsilon: ";
	const std::string& kError = "Epsilon should be (0; 0.1]! ReEnter: ";
	bool isNotError = false;
	double epsilon = 0;
	double min_eps = 1e-307; // number -> 0; need to correct check of interval.
	double max_eps = 0.1;

	std::cout << kMessage;
	do {
		CheckNum(std::cin, epsilon);
		isNotError = IsInRange(min_eps, max_eps, epsilon);
		if (!isNotError) {
			std::cout << kError;
		}
	} while (!isNotError);

	return epsilon;
}