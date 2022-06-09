#pragma once
#include <iostream>
#include "check_num.h"
#define CLEAR_LINE() (std::cout << "\033[2K")
#define GO_UP_LINE() (std::cout << "\033[1A")

void Clear(const int&);

template<class T>
bool IsLess(const T& x, const T& y) {
	return x > y;
}

template<class T>
bool IsInRange(const T& x, const T& y, const T& a) {
	return a >= x && a <= y;
}

double InputA();

double InputB(const double& a);

int InputN();

double InputEpsilon();