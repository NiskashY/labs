#include <iostream>
/*
	Перенести из созданного списка в новый список все элементы, 
	находящиеся между вершиной и максимальным элементом.
*/

class Stack {
private:
	// information
	int info_ = 0;
	Stack* next = nullptr; // next element
	Stack* begin = nullptr; // peek of Stack
public:
	// push, pop, top, clear
	Stack(int i) { info_ = i; }

	Stack() = default;

	void push(int info) {
		Stack* tmp = new Stack(info);
		tmp->next = begin;
		begin = tmp;
	}

	void view() {
		Stack* tmp = begin;
		while (tmp != nullptr) {
			std::cout << tmp->info_ << std::endl;
			tmp = tmp->next;
		}
	}

	void peek() {
		if (begin != nullptr) { 
			std::cout << begin->info_ << std::endl;
		}

	}

	void pop() {
		if (begin != nullptr) {
			Stack* tmp = begin;
			begin = begin->next;
			delete tmp;
		}
		else {
			std::cout << "Pop: Stack is empty!\n";
		}
	}

	void clear() {
		Stack* tmp;
		while (begin != nullptr) {
			tmp = begin;
			begin = begin->next;
			delete tmp;
		}

		std::cout << "Clear: Now stack is empty.\n";
	}

	void SortAdress() {

	}
};

int main() {
	Stack* stack = new Stack;


	delete stack;
	return 0;
}