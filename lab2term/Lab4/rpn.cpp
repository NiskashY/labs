#include "rpn.h"

double CheckNum() {
	double var;

	while (!(std::cin >> var) || std::cin.get() != '\n') {
		std::cout << "Error! Something go wrong ReEnter: ";
		std::cin.clear();
		while (std::cin.get() != '\n');
	}

	return var;
}

void InputValueOfSymbols(Type*& symbols, std::string& request, int& amount_of_symbols) {
	int index = 0;
	for (auto& i : request) {
		if (i >= 'a' && i <= 'z' && !isInSymbols(symbols, i, index)) {
			symbols[index].symbol = i;
			std::cout << "Input '" << i << "' value: ";
			symbols[index].value = CheckNum();
			index++;
		}
	}
	amount_of_symbols = index;
}

bool isInSymbols(Type*& symbols, char character, int current_size) {
	for (int i = 0; i < current_size; ++i) {
		if (symbols[i].symbol == character) {
			return true;
		}
	}
	return false;
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
	Stack<Type>* stack = new Stack<Type>();

	for (auto& i : result) {
		if (i >= 'a' && i <= 'z') {
			int index_tmp_first = FindIndexSymbolValue(symbols, size, i);
			auto item = symbols[index_tmp_first].value;
			stack->push({ i, item });
		}
		else {
			auto first = stack->peek();
			stack->pop();
			auto second = stack->peek();
			stack->pop();
			Type R = { 'R', 0 };

			switch (i) {
			case '+': {
				R.value = second.value + first.value;
				break;
			}
			case '-': {
				R.value = second.value - first.value;
				break;
			}
			case '*': {
				R.value = second.value * first.value;
				break;
			}
			case '/': {
				R.value = second.value / first.value;
				break;
			}
			}
			stack->push(R);

		}
	}

	return stack->peek().value;
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
				else if (stack->peek() == '+' || stack->peek() == '-') {
					result.push_back(stack->peek());
					stack->pop();
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
