#include <iostream>

#include "menues.h"
#include "check_num.h"
#include "validation.h"

// if it goes inf in calculate = graphic in 0 goes to inf
// Task: e^3 / x^3 - sin^3(x)

double Function(const double& x);
double Method(double (*func)(const double&), double&, double&, int&);
double MethodAuto(const double&, const double&, const double&, int&, bool&);
double CalcAverage(const double& a, const double& b, const int& n);
double CalcTrapeze(const double& a, const double& b, const int& n);

void Calculate(int&, double&, double&);
void CalculateByParts(double&, double&);
void CalculateByEpsilon(double&, double&);
void CalculateByAutoMethod(const double& a, const double& b);

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
	double h = (b - a) / n;

	for (double x = a; x < b + h / 4; x += h) {
		s += func(x) + 4 * func(x + h / 2) + func(x + h);
	}

	return  s * h / 6;
}

double CalcTrapeze(const double& a, const double& b, const int& n) {
	double h = (b - a) / (double)n;
	double result = 0;

	for (int i = 2; i <= n; ++i) {
		result += Function(a + h * (i - 1));	// calc Summ(yi)
	}
	result += (Function(a) + Function(b) ) / 2.;
	
	return result * h;
}

double CalcAverage(const double& a, const double& b, const int& n) {
	double h = (b - a) / (double)n;
	double result = 0;

	for (double x = a; x <= b; x += h) {
		result += Function((x + x + h) / 2.);
	}

	return h * result;
}

double MethodAuto(const double& a, const double& b, const double& epsilon, int& n, bool& isFound) {
	double result_trapeze = 0;
	double result_average = 0;
	const int max_n = (1 << 19);

	do {
		result_trapeze = CalcTrapeze(a, b, n);
		result_average = CalcAverage(a, b, n);
		isFound = (fabs(result_trapeze - result_average) < epsilon);
		if (isFound) {
			break;
		}
		n *= 2;
	} while (!isFound && n <= max_n);

	return (result_trapeze + 2 * result_average) / 3;
}

void Calculate(int& tmp, double& a, double& b) {
	const char* const& kMenuCalc = "1 - By number of partitions\n2 - By Epsilon\n3 - By AutoMethod\nelse - back\nYour choice: ";

	std::cout << kMenuCalc;
	CheckNum(std::cin, tmp);
	std::cout << '\n';

	if (tmp == 1) {
		CalculateByParts(a, b);
	}
	else if (tmp == 2) {
		CalculateByEpsilon(a, b);
	}
	else if (tmp == 3) {
		CalculateByAutoMethod(a, b);
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
	const long long maximum_n= (1ll << 19); // ~ 500'000 (more my pc can't compute :D)

	while (n <= maximum_n) {
		n *= 2;
		I2 = Method(Function, a, b, n);
		if ((fabs(I1 - I2) <= epsilon)) {
			n /= 2;
			break;
		}
		I1 = I2;
	}
	
	if (n > maximum_n) {
		std::cout << kAccuracy << "\n\n";
	}
	else {
		ShowAnswer(I1, n);
	}
}

void CalculateByAutoMethod(const double& a, const double& b) {
	double epsilon = InputEpsilon();
	int n = 2;
	bool isFound = false;
	double result = MethodAuto(a, b, epsilon, n, isFound);

	if (isFound) {
		ShowAnswer(result, n);
	}
	else {
		const char kAccuracy[] = "Accuracy not achieved";
		std::cout << kAccuracy << "\n\n";
	}
}
