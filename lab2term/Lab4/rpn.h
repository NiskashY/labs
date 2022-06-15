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
double CalculateReversePolishNotation(const mtl::string&, mtl::vector<Type>&, bool&);
int FindIndexSymbolValue(mtl::vector<Type>& symbols, char item);

bool isInSymbols(mtl::vector<Type>&, char);
void InputValueOfSymbols(mtl::vector<Type>&, const mtl::string&);

template <class T>
void CheckNum(T& var) {
	while (!(std::cin >> var) || std::cin.get() != '\n') {
		std::cout << "Error! Something go wrong ReEnter: ";
		std::cin.clear();
		while (std::cin.get() != '\n');
	}
}