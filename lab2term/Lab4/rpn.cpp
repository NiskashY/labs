#include "rpn.h"

void InputValueOfSymbols(mtl::vector<Type>& symbols, const mtl::string& request) {
	for (const auto& item : request) {
		if (item >= 'a' && item <= 'z' && !isInSymbols(symbols, item)) {
			std::cout << "Input '" << item << "' value: ";
			double value = 0;
			CheckNum(value);
			symbols.push_back(Type{item, value});
		}
	}
}

bool isInSymbols(mtl::vector<Type>& symbols, char character) {
	for (size_t i = 0; i < symbols.size(); ++i) {
		if (symbols[i].symbol == character) {
			return true;
		}
	}
	return false;
}

int FindIndexSymbolValue(mtl::vector<Type>& symbols, char item) {
	for (size_t i = 0; i < symbols.size(); ++i) {
		if (symbols[i].symbol == item) {
			return i;
		}
	}
	return -1; // not exist;
}

double CalculateReversePolishNotation(const mtl::string& result, mtl::vector<Type>& symbols, bool& isDenominator) {
	Stack<Type>* stack = new Stack<Type>();

	for (auto& i : result) {
		if (i >= 'a' && i <= 'z') {
			int i_index = FindIndexSymbolValue(symbols, i);
			stack->push(Type{ i, symbols[i_index].value });
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
				if (!first.value) {
					isDenominator = true;
					std::cout << "\nDenominator = 0! Input values again.\n";
					return 0;
				}
				R.value = second.value / first.value;
				isDenominator = false;
				break;
			}
			}
			stack->push(R);

		}
	}

	return stack->peek().value;
}

mtl::string CreateReversePolishNotation(mtl::string& request) {
	Stack<char>* stack = new Stack<char>();
	mtl::string result;

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
