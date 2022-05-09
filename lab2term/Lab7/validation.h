#pragma once
#include <iostream>
#include "check_num.h"

double InputA();

double InputB(const double&);

int InputM();

int InputN(const int&);

template<class T>
bool IsLess(const T& x, const T& y) {
	return x > y;
}