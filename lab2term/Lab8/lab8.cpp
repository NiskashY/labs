#include <iostream>

#include "menues.h"
#include "check_num.h"
#include "validation.h"

// if it goes inf in calculate = graphic in 0 goes to inf
// Task: e^3 / x^3 - sin^3(x)

double Function(const double& x);
double Method(double (*func)(const double&), double&, double&, int&);
void Calculate(int&, double&, double&);
void CalculateByParts(double&, double&);
void CalculateByEpsilon(double&, double&);

int main() {
	double a = 4, b = 7;
	
	while (true) {
		system("cls");
		ShowHeader(a, b);

		int tmp = 0;
		CheckNum(std::cin, tmp);
		std::cout << '\n';

		if (tmp == 1) {
			a = InputA();
			b = InputB(a);
		}
		else if (tmp == 2) {
			Calculate(tmp, a, b);
		} 
		else {
			std::cout << "\n\t\tBye!" << '\n';
			break;
		}
	}

	return 0;
}

double Function(const double& x) {
	return exp(x) / (x * x * x) - (sin(x) * sin(x) * sin(x));
}

double Method(double (*func)(const double&), double& a, double& b, int& n) {
	double s = 0;
	double h = 0;
	h = (b - a) / n;

	for (double x = a; x < b + h / 4; x += h) {
		s += func(x) + 4 * func(x + h / 2) + func(x + h);
	}

	return  s * h / 6;
}

void Calculate(int& tmp, double& a, double& b) {
	const std::string& kMenuCalc = "1 - By number of partitions\n2 - By Epsilon\nelse - back\nYour choice: ";

	std::cout << kMenuCalc;
	CheckNum(std::cin, tmp);
	std::cout << '\n';

	if (tmp == 1) {
		CalculateByParts(a, b);
	}
	else if (tmp == 2) {
		CalculateByEpsilon(a, b);
	}
	else {
		return;
	}

	system("pause");
}

void CalculateByParts(double& a, double& b) {
	int n = InputN();
	ShowAnswer(Method(Function, a, b, n), n);
}

void CalculateByEpsilon(double& a, double& b) {
	const char kAccuracy[] = "Accuracy not achieved";
	int n = 2; // start amount of partitions.
	double epsilon = InputEpsilon();
	double I1 = Method(Function, a, b, n);
	double I2 = 0;

	int i = 0;
	const int maximum_iterations = 100;

	while (i++ < maximum_iterations) {
		n *= 2;
		I2 = Method(Function, a, b, n);
		if ((fabs(I1 - I2) <= epsilon)) {
			n /= 2;
			break;
		}
		I1 = I2;
	}
	
	if (i == maximum_iterations) {
		std::cout << kAccuracy << "\n\n";
	}
	else {
		ShowAnswer(I1, n);
	}
}
