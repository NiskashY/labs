#pragma once
#include <iostream>
#include "check_num.h"
#define CLEAR_LINE() (std::cout << "\033[2K")
#define GO_UP_LINE() (std::cout << "\033[1A")

double InputA();

double InputB(const double&);

int InputM();

int InputN(const int&);

template<class T>
bool IsLess(const T& x, const T& y) {
	return x >= y;
}