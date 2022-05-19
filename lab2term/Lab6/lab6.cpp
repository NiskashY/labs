#include <iostream>
#include <cmath>
#include <iomanip>
#include "validation.h"

// e^x / x^3 - sin^3(x) - 2

double CheckNum();

inline double CalculateFunction(double x);

void CalculateVergstainMethod(const double& a, const double& b, const double& epsilo);

void FindSimpleRoots(double&, double&, double&);

void FindSpecialRoots(double&, double&);

int main() {
	double a = 4;
	double b = 7;
	double h = 0.1;

	const std::string kMenu = "1 - Input A B H\n2 - Find Simple Roots\n3 - Find Special Roots\nanother symbol - EXIT\nYour choice: ";
	while (true) {
		system("cls");
		char choice;
		std::cout << std::defaultfloat << "\tCurrent a = " << a << "; b = " << b << "; h = " << h << "\n";
		std::cout << kMenu;
		CheckNum(choice);
		switch (choice) {
		case '1': {
			do {
				a = InputA();
				b = InputB();
			} while (isALessB(a, b));

			h = InputH();
			break;
		}
		case '2': {
			FindSimpleRoots(a, b, h);
			break;
		}
		case '3': {
			FindSpecialRoots(a, b);
			break;
		}
		default:
			std::cout << "\n\t\t\t\tBye!";
			return 0;
		}

		system("pause");
	}

	return 0;
}

inline double CalculateFunction(double x) {
	return exp(x) / (x * x * x) - sin(x) * sin(x) * sin(x) - 2;
}

void CalculateVergstainMethod(const double& a, const double& b, const double& epsilo) {
	double x1 = a;
	double x2 = b;
	int i = 0;

	if (x2 - x1 > epsilo) {
		double y1 = CalculateFunction(x1);
		double y2 = CalculateFunction(x2);
		do {
			++i;
			double tmp = x2;
			x2 = x1 - (y1 * (x1 - x2)) / (y1 - y2);

			if (fabs(x2 - x1) <= epsilo) {
				break;
			}

			x1 = tmp;
			y1 = CalculateFunction(x1);
			y2 = CalculateFunction(x2);
		} while (i < 100);
	}

	if (i == 100 || fabs(CalculateFunction(x2)) > epsilo) {
		std::cout << std::fixed << std::setw(18) << "FUNCTION DIVERGES" << '\n';
		return;
	}
	else {
		std::cout << std::fixed << std::setw(18) << std::setprecision(14) << x2  << ' '
				  << std::setw(18) << std::setprecision(14) << CalculateFunction(x2) << " iteration = " 
				  << std::setw(3) << i << '\n';
	}
}

void FindSimpleRoots(double& a, double& b, double& h) {
	const double e = 1e-6;
	int precision = 1;
	for (double eps = 0.1; eps >= e; eps /= 10, ++precision) {
		std::cout << "\nEpsilo = ";
		std::cout << std::fixed << std::setw(8) << std::left << std::setprecision(precision) << eps << ':';
		int root_count = 0;
		for (double i = a; i < b + h / 4; i += h) {
			double left = CalculateFunction(i);
			double right = CalculateFunction(i + h);

			if (left * right < 0) {
				++root_count;
				std::cout << "\n\t\t\t" << '#' << root_count << " Root ";
				CalculateVergstainMethod(i, i + h, eps);
			}
		}
		if (!root_count) {
			std::cout << "\tNo roots for this parametrs in interval.";
		}
		std::cout << "\n";
	}
}

void FindSpecialRoots(double& a, double& b) {
	const double maximum_epsilon = 1e-6;
	int precision = 1;
	for (double eps = 0.1; eps >= maximum_epsilon; eps /= 10, ++precision) {
		std::cout << "\nEpsilon = ";
		std::cout << std::fixed << std::setw(8) << std::left << std::setprecision(precision) << eps << ':';
		int root_count = 0;
		
		double begin = 0;
		double end = 0;
		bool isSetBegin = false;
		for (double i = a; i < b + eps / 4; i += eps / 10) {
			double y = fabs(CalculateFunction(i));
			if (y < eps && !isSetBegin) {
				begin = i;
				isSetBegin = true;
			} else if (y > eps && isSetBegin) {
				end = i;
				std::cout << "\nInterval, where roots are exists - [" << begin << ';' << end << "]";
				isSetBegin = false;
				root_count++;
			}
		}
		if (!root_count) {
			std::cout << "\tNo roots for this parametrs in interval.";
		}
		std::cout << "\n";
	}
}