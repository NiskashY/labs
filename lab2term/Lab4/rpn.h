#pragma once
#include <iostream>
#include "stack.h"

struct Type {
	char symbol = 'a' - 1;
	double value = 0;
};

std::string CreateReversePolishNotation(std::string&);
double CalculateReversePolishNotation(std::string&, Type*&, int);
int FindIndexSymbolValue(Type*& symbols, const int size, char item);

bool isInSymbols(Type*&, char, int);
void InputValueOfSymbols(Type*&, std::string&, int&);