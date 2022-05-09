#include <iostream>
#include <string>

#include "check_num.h"
#include "validation.h"
#include <iomanip>

double Function(double& x) {
	return exp(x) / (x * x * x) - (sin(x) * sin(x) * sin(x));
}

void ShowTableM_X(double*& m_x, int& m);

void InputParameters(double&, double&, int&, int&, double*&, double&, double&);

void Calculate(double&, double&, int&, int&, double*&, double&, double&);

double FindH(const double&, const double&, const int&);

bool Method(double&, double*, int&, double&);

double CalculateN2(double&, double&, double&, double&);

int main() {
	double a = 0, b = 0;
	int m = 0, n = 0;
	double h = 0;
	double h1 = 0;
	double* m_x = nullptr;
	const std::string& kTask = "\t\tTASK: e^x / x^3 - sin(x)^3";
	const std::string& kMenu = "\n1 - Input Parameters\n2 - Calculate\nelse - exit\nYour choice: ";

	while (true) {
		system("cls");
		std::cout.unsetf(std::ios::fixed);
		std::cout << kTask << '\n'
			<< "a = " << a << " b = " << b << " m = " << m << " n = " << n << "\n";

		ShowTableM_X(m_x, m);

		std::cout << kMenu;
		int tmp = 0;
		CheckNum(std::cin, tmp);
		std::cout << '\n';

		if (tmp == 1) {
			InputParameters(a, b, m, n, m_x, h, h1);
			std::cout << "Done!\n\n";
		}
		else if (tmp == 2) {
			Calculate(a, b, m, n, m_x, h, h1);
			std::cout << "\n";
		}
		else {
			break;
		}
		system("pause");
	}
	
	if (m_x != nullptr) {
		delete[] m_x;
	}

	return 0;
}

void ShowTableM_X(double*& m_x, int& m) {
	if (m_x != nullptr) {
		std::cout << "-------x--------f(x)-------\n";
		for (int i = 0; i < m; ++i) {
			std::cout << std::fixed << std::left << '#' << std::setw(3) << i + 1 << ' '
				<< std::setw(10) << m_x[i] << std::setw(10) << Function(m_x[i]) << '\n';
		}
		std::cout << "---------------------------\n";
	}
}

void InputParameters(double& a, double& b, int& m, int& n, double*& m_x, double& h, double& h1) {
	a = InputA();
	b = InputB(a);
	m = InputM();
	n = InputN(m);

	h = FindH(a, b, m);
	h1 = FindH(a, b, n);

	if (m_x != nullptr) { // if m_x not first initialisation
		delete[] m_x;
		m_x = nullptr;
	}

	m_x = new double[m];

	double x = 0;
	int i = 0;
	for (x = a, i = 0; i < m; ++i, x += h) {
		m_x[i] = x;
	}
}

void Calculate(double& a, double& b, int& m, int& n, double*& m_x, double& h, double& h1) {
	double x = a;
	for (int i = 0; i < n; ++i, x += h1) {
		double method_result = 0;
		if (Method(x, m_x, m, method_result)) { // Check if xt ok 
			std::cout << std::fixed << std::left
				<< '#' << std::setw(3) << i + 1 << ' '
				<< "xt = " << std::setw(15) << x
				<< "\tf*(x) = " << std::setw(15) << method_result
				<< "\tDiff = " << std::setw(15) << Function(x) - method_result << '\n';
		}
	}
}

double FindH(const double& a, const double& b, const int& amount) { // amount == (m || n)
	return (b - a) / ((double)amount - 1);
}

bool Method(double& xt, double* m_x, int& m, double& result) {
	if (xt < m_x[0] || xt > m_x[m - 1]) {
		const std::string& kError = "xt outside the table!";
		std::cout << kError << '\n';
		return false;
	} else {
		int i = 1;
		while (xt > m_x[i] && i < m) {
			++i;
		}
		--i;

		result = CalculateN2(m_x[i - 1], m_x[i], m_x[i + 1], xt);
	}

	return true;
}

double CalculateN2(double& x_i_prev, double& x_i, double& x_i_next, double& xt) {
	double y_i_prev = Function(x_i_prev);
	double y_i = Function(x_i);
	double y_i_next = Function(x_i_next);

	double diff_y_prev_cur = y_i - y_i_prev;
	double diff_y_next_cur = y_i - y_i_next;
	double diff_x_prev_cur = x_i - x_i_prev;
	double diff_x_cur_next = x_i - x_i_next;
	double diff_x_prev_next = x_i_prev - x_i_next;
	double diff_xt_prev = xt - x_i_prev;
	double diff_xt_cur = xt - x_i;

	double N1 = y_i_prev + diff_xt_prev * (diff_y_prev_cur / diff_x_prev_cur);

	return N1 + diff_xt_prev * diff_xt_cur *
		((diff_y_prev_cur / diff_x_prev_cur - diff_y_next_cur / diff_x_cur_next)
		/ diff_x_prev_next);
}
