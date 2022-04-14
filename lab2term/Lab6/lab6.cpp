#include <iostream>
#include <cmath>
#include <iomanip>

// e^x / x^3 - sin^3(x) - 2
double CheckNum();

inline double CalculateFunction(double x);

void CalculateVergstainMethod(const double& a, const double& b, const double& epsilo);

double InputH() {
	double h = 0;
	do {
		//- if u input less - it will take too much time to run the program
		//- if u input mroe - it will lead to wrong results
		std::cout << "Input h (interval - [0.000001; 0.4] ";
		h = CheckNum();
	} while (h < 0.000001 || h > 0.4);
	return h;
}

int main() {
	const double a = 4;
	const double b = 7;
	double e = 1e-6;
	double h = 0;

	h = InputH();

	int precision = 1;
	std::cout << '\n';
	std::cout << std::fixed << std::setw(7) << "Epsilo";
	std::cout << std::fixed << std::setw(17) << "First Root" << std::setw(7) << "Iter";
	std::cout << std::fixed << std::setw(14) << "Second Root" << std::setw(8) << "Iter";
	std::cout << std::fixed << std::setw(15) << "Third Root" << std::setw(8) << "Iter\n";


	for (double eps = 0.1; eps >= e; eps /= 10, ++precision) {
		std::cout << std::fixed << std::setw(9) << std::left << std::setprecision(precision) << eps << '|';
		for (double i = a; i <= b;) {
			double left = CalculateFunction(i);
			double right = CalculateFunction(i + h);

			if (left * right < 0) {
				//std::cout << "Step number: " << (int) ((i - a) / h) << '\n';
				CalculateVergstainMethod(i, i + h, eps);
			}
			i += h;
		}
		std::cout << '\n';
	}

}

double CheckNum() {
	double var;

	while (!(std::cin >> var) || std::cin.get() != '\n') {
		std::cout << "Error! Something go wrong ReEnter: ";
		std::cin.clear();
		while (std::cin.get() != '\n');
	}

	return var;
}

inline double CalculateFunction(double x) {
	return exp(x) / (x * x * x) - sin(x) * sin(x) * sin(x) - 2;
}

void CalculateVergstainMethod(const double& a, const double& b, const double& epsilo) {
	double x1 = a;
	double x2 = b;

	double y1 = CalculateFunction(x1);
	double y2 = CalculateFunction(x2);
	int i = 0;
	do {
		double tmp = x2;
		x2 = x1 - (y1 * (x1 - x2)) / (y1 - y2);

		if (fabs(x2 - x1) <= epsilo) {
			break;
		}

		x1 = tmp;
		y1 = CalculateFunction(x1);
		y2 = CalculateFunction(x2);
		++i;
		//std::cout << "i - " << i << '\n';
	} while (i < 100);

	if (i == 100) {
		std::cout << std::fixed << std::setw(18) << "NULL" << std::fixed << std::setw(3) << i << '|';
		return;
	}
	else {
		std::cout << std::fixed << std::setw(18) << std::setprecision(14) << x2 << std::setw(3) << i << '|';
	}
}
