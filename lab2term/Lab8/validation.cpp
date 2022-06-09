#include "validation.h"

void Clear(const int& errors) {
	if (errors > 1) {
		GO_UP_LINE();	// macros	-	validation.h
		CLEAR_LINE();	// macros	-	validation.h
	}
}

double InputA() {
	const char* const& kMessage = "Input a: ";
	const char* const& kError = "a must be not equal to zero! ReEnter: ";
	std::cout << kMessage;
	double a = 0;
	int errors = 0;

	do {
		CheckNum(std::cin, a);
		if (!a) {
			errors++;
			Clear(errors);
			std::cout << kError;
		}
	} while (!a);

	return a;
}

double InputB(const double& a) {
	const char* const& kMessage = "Input b: ";
	const char* const& kError = "b must be more than a! ReEnter: ";
	bool isError = false;
	double b = 0;
	int errors = 0;

	std::cout << kMessage;
	do {
		CheckNum(std::cin, b);
		isError = IsLess(a, b);
		if (isError) {
			errors++;
			Clear(errors);
			std::cout << kError;
		}
	} while (isError);

	return b;
}

int InputN() {
	const char* const& kMessage = "Input n: ";
	const char* const& kError = "n must be not less than 1! ReEnter: ";
	bool isError = false;
	int n = 0;
	int min_n = 1;
	int errors = 0;

	std::cout << kMessage;
	do {
		CheckNum(std::cin, n);
		isError = IsLess(min_n, n);
		if (isError) {
			errors++;
			Clear(errors);
			std::cout << kError;
		}
	} while (isError);

	return n;
}

double InputEpsilon() { // ia tyt xotel postavit granici ot 1e-6, do 0.5 :|
	const char* const& kMessage = "Input epsilon: ";
	const char* const& kError = "Epsilon should be (0; 0.1]! ReEnter: ";
	bool isNotError = false;
	double epsilon = 0;
	const double min_eps = 1e-307; // number -> 0; need to correct check of interval.
	const double max_eps = 0.1;
	int errors = 0;

	std::cout << kMessage;
	do {
		CheckNum(std::cin, epsilon);
		isNotError = IsInRange(min_eps, max_eps, epsilon);
		if (!isNotError) {
			errors++;
			Clear(errors);
			std::cout << kError;
		}
	} while (!isNotError);

	return epsilon;
}