#include <iostream>
#include "stack.h"

int main() {
	Stack<char>* stack = new Stack<char>();
	std::string request, result;

	std::cin >> request;

	for (const auto& i : request) {
		if (i != '+' && i != '-' && i != '*' && i != '/') {
			result.push_back(i);
		}
		else {
			switch (i) {
			case '+': case '-': {
				stack->push(i);
				break;
			}
			case '*': case '/': {
				while (!stack->empty()) {
					result.push_back(stack->peek());
					stack->pop();
				}
			}
		}
	}


	return 0;
}