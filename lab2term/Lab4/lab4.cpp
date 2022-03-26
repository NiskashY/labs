#include <iostream>
#include "stack.h"
#include <set>

struct Type {
	char symbol = 'a' - 1;
	double value = 0;
};

std::string CreateReversePolishNotation(std::string&);
double CalculateReversePolishNotation(std::string&, Type*&, int);
int FindIndexSymbolValue(Type*& symbols, const int size, char item);

double CheckNum();

bool isInSymbols(Type*&, char, int);
void InputValueOfSymbols(Type*&, std::string&, int&, int&);

void Test1();
void Test2();
void Test3();
void Test4();
void RunTests();

int main() {
	std::string request, result;
	//RunTests();

	std::cout << "Input request: ";
	std::cin >> request;
	result = CreateReversePolishNotation(request);
	std::cout << "Result RevePN: " << result << '\n';

	Type* symbols = new Type[request.size()];
	int index = 0, amount_of_symbols = 0;

	InputValueOfSymbols(symbols, request, index, amount_of_symbols);

	double answer = CalculateReversePolishNotation(result, symbols, amount_of_symbols);

	std::cout << answer << '\n';
	return 0;
}

int FindIndexSymbolValue(Type*& symbols, const int size, char item) {
	for (int i = 0; i < size; ++i) {
		if (symbols[i].symbol == item) {
			return i;
		}
	}

	return -1; // not exist;
}

double CalculateReversePolishNotation(std::string& result, Type*& symbols, const int size) {
	Stack<char>* stack = new Stack<char>();
	double R = 0;

	for (auto& i : result) {
		if (i >= 'a' && i <= 'z') {
			stack->push(i);
		}
		else {
			int index_tmp_first = FindIndexSymbolValue(symbols, size, stack->peek());
			stack->pop();


				int index_tmp_second = FindIndexSymbolValue(symbols, size, stack->peek());
				double first = 0;
				if (index_tmp_first != -1) {
					first = symbols[index_tmp_first].value;
				}
				else {
					first = R;
				}
					
				double second = symbols[index_tmp_second].value;

				switch (i) {
				case '+': {
					R = second + first;
					break;
				}
				case '-': {
					R = second - first;
					break;
				}
				case '*': {
					R = second * first;
					break;
				}
				case '/': {
					R = second / first;
					break;
				}
				}
				stack->pop();
				stack->push('R');
			
		}
	}

	return R;
}

void InputValueOfSymbols(Type*& symbols, std::string& request, int& index, int& amount_of_symbols ) {
	for (auto& i : request) {
		if (i >= 'a' && i <= 'z' && !isInSymbols(symbols, i, index)) {
			symbols[index].symbol = i;
			std::cout << "Input '" << i << "' value: ";
			symbols[index].value = CheckNum();
			index++;
		}
	}

	amount_of_symbols = index;

	for (int i = 0; i < amount_of_symbols; ++i) {
		std::cout << symbols[i].symbol << ' ' << symbols[i].value << '\n';
	}
}

double CheckNum() {
	double var;

	while (!(std::cin >> var) || std::cin.get() != '\n') {
		std::cout << "Error! Something go wrong ReEnter: ";
		std::cin.clear();
		while (std::cin.get() != '\n');
	}

	return var;
}

bool isInSymbols(Type*& symbols, char character, int current_size) {
	for (int i = 0; i < current_size; ++i) {
		if (symbols[i].symbol == character) {
			return true;
		}
	}
	return false;
}

std::string CreateReversePolishNotation(std::string& request) {
	Stack<char>* stack = new Stack<char>();
	std::string result;

	for (const auto& i : request) {
		if (i <= 'z' && i >= 'a') {
			result.push_back(i);
		}
		else {
			switch (i) {
			case '+': case '-': {
				if (stack->peek() == '*' || stack->peek() == '/') {
					while (!stack->empty()) {
						result.push_back(stack->peek());
						stack->pop();
					}
				}
				stack->push(i);
				break;
			}
			case '*': case '/': {
				if (stack->peek() == '*' || stack->peek() == '/') {
					result.push_back(stack->peek());
					stack->pop();
				}
				stack->push(i);
				break;
			}
			case '(': {
				stack->push(i);
				break;
			}
			case ')': {
				while (stack->peek() != '(') {
					result.push_back(stack->peek());
					stack->pop();
				}
				stack->pop();
			}
			}
		}
	}
	while (!stack->empty()) {
		result.push_back(stack->peek());
		stack->pop();
	}
	
	return result;
}

void Test1() {
	std::string request, result;

	request = "a+b*(c-d)/e+f";

	result = CreateReversePolishNotation(request);
	/*
	a+b*(c-d)/e+f
	abcd-*e/+f+

	a/(b– c)*(d+e)

	*/
	std::cout << "Test1.\t";
	if (result == "abcd-*e/+f+") {
		std::cout << "Request: " + request + ". Result: " + result + "\tOk!\n";
	}
	else
		std::cout << "Request: " + request + ". Result: " + result + "\tError!\n";
}

void Test2() {
	std::string request, result;

	request = "a/(b-c)*(d+e)";

	result = CreateReversePolishNotation(request);

	std::cout << "Test2.\t";
	if (result == "abc-/de+*") {
		std::cout << "Request: " + request + ". Result: " + result + "\tOk!\n";
	}
	else
		std::cout << "Request: " + request + ". Result: " + result + "\tError!\n";
}

void Test3() {
	std::string request, result;

	request = "(a+b)*(c-d)/e";

	result = CreateReversePolishNotation(request);

	std::cout << "Test3.\t";
	if (result == "ab+cd-*e/") {
		std::cout << "Request: " + request + ". Result: " + result + "\tOk!\n";
	}
	else
		std::cout << "Request: " + request + ". Result: " + result + "\tError!\n";
}

void Test4() {
	std::string request, result;

	request = "a-(b+c*d)/e";

	result = CreateReversePolishNotation(request);

	std::cout << "Test4.\t";
	if (result == "abcd*+e/-") {
		std::cout << "Request: " + request + ". Result: " + result + "\tOk!\n";
	}
	else
		std::cout << "Request: " + request + ". Result: " + result + "\tError!\n";
}

void RunTests() {
	Test1();
	Test2();
	Test3();
	Test4();
}