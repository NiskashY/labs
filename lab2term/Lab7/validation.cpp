#include "validation.h"

void Clear(const int& errors) {
	if (errors > 1) {
		GO_UP_LINE();	// macros	-	validation.h
		CLEAR_LINE();	// macros	-	validation.h
	}
}

double InputA() {
	const char* const& kMessage = "Input a: ";
	std::cout << kMessage;
	double a = 0;
	CheckNum(std::cin, a);
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
			++errors;
			Clear(errors);
			std::cout << kError;
		}
	} while (isError);

	return b;
}

int InputM() {
	const char* const& kMessage = "Input m: ";
	const char* const& kError = "m must be more than 1! ReEnter: ";
	bool isError = false;
	int m = 0;
	// min_m = 2, because if m (or n) <= 1  =>
	// => in FindH(...) the denominator == 0 || (denominator < 0 => h < 0)
	const int min_m = 1; 
	int errors = 0;
	
	std::cout << kMessage;
	do {
		CheckNum(std::cin, m);
		isError = IsLess(min_m, m);
		if (isError) {
			++errors;
			Clear(errors);
			std::cout << kError;
		}
	} while (isError);

	return m;
}

int InputN(const int& m) {
	const char* const& kMessage = "Input n: ";
	const char* const& kError = "n must be greater than m! ReEnter: ";
	bool isError = false;
	int n = 0;
	int errors = 0;

	std::cout << kMessage;
	do {
		CheckNum(std::cin, n);
		isError = IsLess(m, n);
		if (isError) {
			++errors;
			Clear(errors);
			std::cout << kError;
		}
	} while (isError);

	return n;
}
