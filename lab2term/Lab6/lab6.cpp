#include <iostream>
#include <cmath>
#include <iomanip>

// e^x / x^3 - sin^3(x) - 2

inline double CalculateFunction(double x) {
	return exp(x) / (x * x * x) - sin(x) * sin(x) * sin(x) - 2;
}

double CalculateVergstainMethod(const double &a, const double& b, const double& epsilo) {
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
		std::cout << "i - " << i << '\n';
	} while (i < 100);

	if (i == 100) {
		std::cout << "over 100 iterations.\n";
		return 0;
	}

	return x2;
}


int main() {
	const double a = 4;
	const double b = 7;
	const double e = 0.0001;

	double first_root = CalculateVergstainMethod(a, b, e);
	std::cout << "\n";
	double second_root = CalculateVergstainMethod(a, first_root - 1, e);	
	std::cout << "\n";
	double third_root = CalculateVergstainMethod(first_root + 1, b, e);


	std::cout << "First  Root - " << std::fixed << std::setprecision(20) << first_root << '\n';
	std::cout << "Second Root - " << std::fixed << std::setprecision(20) << second_root << '\n';
	std::cout << "Third  Root - " << std::fixed << std::setprecision(20) << third_root << '\n';

}