#include <iostream>
#include <string>
#include "stack.h"
#include "rpn.h"
#include "tests.h"

bool isRequestCorrect(std::string&);
bool isOperation(char i);

int main() {
	std::string request, result;
	RunTests();

	std::cout << "Input request: ";
	do {
		getline(std::cin, request);
	} while (!isRequestCorrect(request));

	result = CreateReversePolishNotation(request);
	std::cout << "Result RevePN: " << result << '\n';

	Type* symbols = new Type[request.size()]; // Array for symbols. In functions below i check for existing symbols in this array;
	int amount_of_symbols = 0;

	InputValueOfSymbols(symbols, request, amount_of_symbols);

	double answer = CalculateReversePolishNotation(result, symbols, amount_of_symbols);

	std::cout << "\nAnswer: " << answer << '\n';
	return 0;
}

bool isOperation(char i) {
	return i == '+' || i == '-' || i == '*' || i == '/';
}

bool isRequestCorrect(std::string& request) {
	Stack<char>* brackets = new Stack<char>();
	bool answer = true;
	char prev_symbol = 'a' - 1;
	
	// check for brackets sequence and contains unnecessary characters
	for (const auto& i : request) {
		if (i == '(') {
			if (prev_symbol == 'a' - 1 || isOperation(prev_symbol) || prev_symbol == '(') {
				brackets->push(i);
				prev_symbol = i;
				continue;
			}
			std::cout << "No operation Before Bracket! ReEnter: ";
			return false;
		}
		else if (i == ')') {
			prev_symbol = i;
			if (brackets->peek() == '(') {
				brackets->pop();
				continue;
			}
			else {
				answer = false;
				break;
			}
		}
		else if (isOperation(i)) {
			if (prev_symbol >= 'a' && prev_symbol <= 'z' ||  prev_symbol == ')') {
				prev_symbol = i;
				continue;
			}
			std::cout << "Something wrong with Operations! ReEnter: ";
			return false;
		}
		else if (i >= 'a' && i <= 'z') {
			if (prev_symbol == 'a' - 1 || isOperation(prev_symbol) || prev_symbol == '(' ) {
				prev_symbol = i;
				continue;
			}
			std::cout << "Something wrong with character sequence! ReEnter: ";
			return false;
		}
		
		std::cout << "Invalid request! ReEnter: ";
		return false;
	}

	if (!brackets->empty() || answer == false) {
		std::cout << "Incorrect brackets sequence! ReEnter: ";
		return false;
	}

	return true;
}
