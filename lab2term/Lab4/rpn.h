#pragma once
#include <iostream>
#include "stack.h"
#include "MintLibString.h"

namespace mtl = MintLib;

struct Type {
	char symbol = 'a' - 1;
	double value = 0;
};

mtl::string CreateReversePolishNotation(mtl::string&);
double CalculateReversePolishNotation(const mtl::string&, Type*&, int, bool&);
int FindIndexSymbolValue(Type*& symbols, const int size, char item);

bool isInSymbols(Type*&, char, int);
void InputValueOfSymbols(Type*&, const mtl::string&, int&);

template <class T>
void CheckNum(T& var) {
	while (!(std::cin >> var) || std::cin.get() != '\n') {
		std::cout << "Error! Something go wrong ReEnter: ";
		std::cin.clear();
		while (std::cin.get() != '\n');
	}
}