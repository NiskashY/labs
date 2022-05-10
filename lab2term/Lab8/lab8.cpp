#include <iostream>

#include "check_num.h"
#include "validation.h"
#include <iomanip>

double Function(const double& x) {
	return exp(x) / (x * x * x) - (sin(x) * sin(x) * sin(x));
}

double Method(double (*func)(const double&), double&, double&, int&);

void Calculate(int&, double&, double&);

int main() {
	double a = 4, b = 7;
	
	const std::string& kTask = "\t\tTASK: e^x / x^3 - sin(x)^3";
	const std::string& kMenu = "\n1 - Input Parameters\n2 - Calculate\nelse - exit\nYour choice: ";

	while (true) {
		system("cls");
		std::cout.unsetf(std::ios::fixed);
		std::cout << kTask << '\n';

		if (a == 4 && b == 7) { std::cout << "default "; }
		
		std::cout << "parameters: " << "a = " << a << " b = " << b << "\n";

		std::cout << kMenu;
		int tmp = 0;
		CheckNum(std::cin, tmp);
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

void Calculate(int& tmp, double& a, double& b) {
	const std::string& kMenuCalc = "\n1 - By number of partitions\n2 - By Epsilon\nelse - back\nYour choice: ";
	const std::string& kAccuracy = "Accuracy not achieved";

	std::cout << kMenuCalc;
	CheckNum(std::cin, tmp);
	int n = 0, i = 0;
	double I1 = 0, I2 = 0;

	if (tmp == 1) {
		n = InputN();
		I1 = Method(Function, a, b, n);
	}
	else if (tmp == 2) {
		double epsilon = InputEpsilon();
		n = 2; // start amount of partitions.
		I1 = Method(Function, a, b, n);
		while (i++ < 300) {
			n *= n;
			I2 = Method(Function, a, b, n);
			if ((fabs(I1 - I2) <= epsilon)) {
				n /= 2;
				break;
			}
			I1 = I2;
		}
	}
	else {
		return;
	}

	if (i == 300) {
		std::cout << kAccuracy << "\n\n";
	}
	else {
		std::cout << "\nAnswer: I = " << std::fixed << std::setprecision(10) << I1 << "; n = " << n << "\n\n";
	}
	system("pause");
}

double Method(double (*func)(const double&), double& a, double& b, int& n) {
	double s = 0;
	double h = 0;
	double x = 0;

	h = (b - a) / n;			
	x = a;
	
	for (int i = 1; i <= n; i++) {
		s += func(x) + 4 * func(x + h / 2) + func(x + h);
		x += h;
	}

	return  s * h / 6;
}
