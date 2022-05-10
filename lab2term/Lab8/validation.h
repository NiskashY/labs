#pragma once
#include <iostream>
#include "check_num.h"

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