#include "validation_request.h"

void Clear(const int& errors) {
	if (errors > 0) {
		GO_UP_LINE();	// macros	-	validation.h
		CLEAR_LINE();	// macros	-	validation.h
	}
}

bool isOperation(char i) {
	return i == '+' || i == '-' || i == '*' || i == '/';
}

bool isRequestCorrect(mtl::string& request) {
	if (request.empty()) {
		std::cout << "Request is empty! ReEnter: ";
		return false;
	}

	Stack<char>* brackets = new Stack<char>();
	bool answer = true;
	char prev_symbol = 'a' - 1;

	// check for brackets sequence and contains unnecessary characters
	if (isOperation(request.back())) {
		std::cout << "Last symbol cant be operation! ReEnter: ";
		return false;
	}

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
			if (isOperation(prev_symbol) || prev_symbol == '(') {
				std::cout << "Operation not available before ) or prev_symbol == '('. ReEnter: ";
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
			if (prev_symbol >= 'a' && prev_symbol <= 'z' || prev_symbol == ')') {
				prev_symbol = i;
				continue;
			}
			std::cout << "Something wrong with Operations! ReEnter: ";
			return false;
		}
		else if (i >= 'a' && i <= 'z') {
			if (prev_symbol == 'a' - 1 || isOperation(prev_symbol) || prev_symbol == '(') {
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
