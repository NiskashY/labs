#include <iostream>
#include <string>
#include <iomanip>

#include "stack.h"
#include "rpn.h"
#include "tests.h"
#include "validation_request.h"
#include "MintLibString.h"


void MenuCalculate(const mtl::string& request, const mtl::string& result);
void MenuInput(mtl::string& request, mtl::string& result);

int main() {
	RunTests();

	mtl::string request;
	mtl::string result;
	const char* kMenu = "Input request - 1\nCalculate - 2\nExit - else\nYour Choice: ";
	const char* kEmpty = "Empty~";
	while (true) {
		system("cls");

		std::cout << "Request: " << (request.empty() ? kEmpty : request) << '\n';
		std::cout << "RPN:     " << (result.empty() ? kEmpty : result) << "\n\n";
		std::cout << kMenu;
		
		int choice = 0;
		CheckNum(choice);

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

		std::cout << '\n';
		system("pause");
	}

	return 0;
}

void MenuCalculate(const mtl::string& request, const mtl::string& result) {
	if (request.empty()) {
		std::cout << "Request is empty!\n";
		return;
	}

	std::cout << "\nRequest: " << request << "\nRevers Polish: " << result << '\n';

	// Array for symbols. In functions below i check
	// for existing symbols in this array; 26 = letters in alphabet
	Type* symbols = new Type[26]; 
	int amount_of_symbols = 0;

	double answer = 0;
	bool isDenominatorEqualZero = false;
	do {
		InputValueOfSymbols(symbols, request, amount_of_symbols);
		answer = CalculateReversePolishNotation(result, symbols, amount_of_symbols, isDenominatorEqualZero);
	} while (isDenominatorEqualZero);

	std::cout << "\nAnswer: " << answer << '\n';

	delete[] symbols;
}

void MenuInput(mtl::string& request, mtl::string& result) {
	std::cout << "\nInput request: ";
	do {
		MintLib::getline(std::cin, request);
	} while (!isRequestCorrect(request));

	result = CreateReversePolishNotation(request);
	std::cout << "Result RevePN: " << result << '\n';
}
