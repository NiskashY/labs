#include "validation.h"

double InputH() {
	double h = 0;
	do {
		//- if u input less - it will take too much time to run the program
		//- if u input mroe - it will lead to wrong results
		std::cout << "Input H interval - [0.000001; 0.4] ";
		CheckNum(h);
	} while (h < 0.000001 || h > 0.4);
	return h;
}

double InputA() {
	double a = 0;
	do {
		std::cout << "Input A interval - [-10; 10] ";
		CheckNum(a);
	} while (a > 10 || a < -10);
	return a;
}

double InputB() {
	double b = 0;
	do {
		std::cout << "Input B interval - [-10; 10] ";
		CheckNum(b);
	} while (b > 10 || b < -10);
	return b;
}

bool isALessB(double& a, double& b) {
	if (a >= b) {
		std::cout << "\x1b[31m" << "A should be less then B!\n\x1b[0m";
	}
	return a >= b;
}
