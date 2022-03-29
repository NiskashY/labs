#include <iostream>
#include <string>
#include <iomanip>
#include "stack.h"
#include "rpn.h"
#include "tests.h"

bool isRequestCorrect(std::string&);
bool isOperation(char i);
void MenuCalculate(const std::string& request, const std::string& result);
void MenuInput(std::string& request, std::string& result);



int main() {
	RunTests();

	std::string request;
	std::string result;
	const std::string MENU = "Input request - 1\nCalculate - 2\nExit - else\nYour Choice: ";

	while (true) {
		system("cls");
		std::cout << MENU;
		
		int choice = 0;
		choice = CheckNum();

		switch (choice) {
		case 1: {
			MenuInput(request, result);
			break;
		}
		case 2: {
			MenuCalculate(request, result);
			break;
		}
		default: {
			std::cout << std::setw(50) << "Bye!";
			return 0;
		}
		}

		system("pause");
	}

	return 0;
}

void MenuCalculate(const std::string& request, const std::string& result) {
	if (request.empty()) {
		std::cout << "Request is empty!\n";
		return;
	}

	std::cout << "\nRequest: " << request << "\nRevers Polish: " << result << '\n';

	Type* symbols = new Type[request.size()]; // Array for symbols. In functions below i check for existing symbols in this array;
	int amount_of_symbols = 0;

	double answer = 0;
	bool isDenominator = false;
	do {
		InputValueOfSymbols(symbols, request, amount_of_symbols);
		answer = CalculateReversePolishNotation(result, symbols, amount_of_symbols, isDenominator);
	} while (isDenominator);

	std::cout << "\nAnswer: " << answer << '\n';

	delete[] symbols;
}

void MenuInput(std::string& request, std::string& result) {
	std::cout << "\nInput request: ";
	do {
		getline(std::cin, request);
	} while (!isRequestCorrect(request));

	result = CreateReversePolishNotation(request);
	std::cout << "Result RevePN: " << result << '\n';
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
			if (isOperation(prev_symbol)) {
				std::cout << "Operation not available before ) ReEnter: ";
				return false;
			}
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
