#pragma once
#include <iostream>


double InputH();

double InputA();

double InputB();

bool isALessB(double&, double&);

template <class T>
void CheckNum(T& var) {
	while (!(std::cin >> var) || std::cin.get() != '\n') {
		std::cout << "Error! Something go wrong ReEnter: ";
		std::cin.clear();
		while (std::cin.get() != '\n');
	}
}