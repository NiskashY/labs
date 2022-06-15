#include <iostream>
#include <string>
#include <iomanip>

#include "stack.h"
#include "rpn.h"
#include "tests.h"
#include "validation_request.h"
#include "MintLibString.h"

namespace mtl = MintLib;

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
		std::cout << '\n';

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

void MenuInput(mtl::string& request, mtl::string& result) {
	std::cout << "Input request: ";

	do {
		MintLib::getline(std::cin, request);
		Clear();
	} while (!(isRequestCorrect(request)));

	result = CreateReversePolishNotation(request);
	std::cout << "Result RevePN: " << result << '\n';
}

void MenuCalculate(const mtl::string& request, const mtl::string& result) {
	if (request.empty()) {
		std::cout << "Request is empty!\n";
		return;
	}
	
	double answer = 0;
	bool isDenominatorEqualZero = false;
	do {
		mtl::vector<Type> symbols; // Array for symbols. In functions below i check for existing symbols in this array;
		InputValueOfSymbols(symbols, request);
		answer = CalculateReversePolishNotation(result, symbols, isDenominatorEqualZero);
	} while (isDenominatorEqualZero);

	std::cout << "\nAnswer: " << answer << '\n';

}
