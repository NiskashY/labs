#pragma once
#include <iostream>
#include "stack.h"

struct Type {
	char symbol = 'a' - 1;
	double value = 0;
};

std::string CreateReversePolishNotation(std::string&);
double CalculateReversePolishNotation(const std::string&, Type*&, int, bool&);
int FindIndexSymbolValue(Type*& symbols, const int size, char item);

double CheckNum();
bool isInSymbols(Type*&, char, int);
void InputValueOfSymbols(Type*&, const std::string&, int&);