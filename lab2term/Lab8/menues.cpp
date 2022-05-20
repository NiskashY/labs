#include "menues.h"

void ShowAnswer(const double& integral, const int& number_of_parts) {
	std::cout << "\nAnswer: I = " << std::fixed << std::setprecision(10) << integral << "; n = "
		<< number_of_parts << "\n\n";
}

void ShowHeader(const double& a, const double& b) {
	const char kTask[] = "\t\tTASK: e^x / x^3 - sin(x)^3";
	const char kMenu[] = "\n1 - Input Parameters\n2 - Calculate\nelse - exit\nYour choice: ";
	std::cout.unsetf(std::ios::fixed);
	std::cout << kTask << '\n';

	if (a == 4 && b == 7) {
		std::cout << "default ";
	}

	std::cout << "parameters: " << "a = " << a << " b = " << b << "\n";

	std::cout << kMenu;
}