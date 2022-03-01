#include <iostream>
/*
	ѕеренести из созданного списка в новый список все элементы, 
	наход€щиес€ между вершиной и максимальным элементом.
*/

class Stack {
private:
	// information
	int info_ = 0;
	Stack* next = nullptr; // next element
	Stack* begin = nullptr; // peek of Stack / or current element
public:
	// push, pop, top, clear
	Stack(int i) { info_ = i; }

	Stack() = default;

	// Getters
	Stack* GetBegin() {
		return begin;
	}
	
	int GetInfo() {
		return info_;
	}

	Stack* GetNext() {
		return next;
	}

	// Funtions for working with stack
	void push(int info) {
		Stack* tmp = new Stack(info);
		tmp->next = begin;
		begin = tmp;
	}

	void view() {
		Stack* tmp = begin;
		std::cout << "View: \n";
		while (tmp != nullptr) {
			std::cout << tmp->info_ << std::endl;
			tmp = tmp->next;
		}
		std::cout << "\n";
	}

	void peek() {
		if (begin != nullptr) { 
			std::cout << begin->info_ << std::endl;
		}
		else {
			std::cout << "Peek: Stack is empty!\n";
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
		Stack* limit = nullptr, *tmp;

		if (begin->next->next == nullptr) {
			std::cout << "SortAdress: Stack is empty!\n";
			return;
		}

		// ƒобавл€ем элемент, чтобы сортировка корректно работала, в конце его нужно удалить
		const int TMP_FOR_DELETE = -1;
		push(TMP_FOR_DELETE); 

		std::cout << "SortAdress: Sort of stack - ";
		// 1 -> 4 -> 3 -> 0 -> nullptr
		// 1 -> 4 -> 0 -> nullptr
		// 1 -> 
		do {
			for (tmp = begin; tmp->next->next != limit; tmp = tmp->next)
				if (tmp->next->info_ > tmp->next->next->info_) {
					// вы двигаем весь стек после элемента на вправо грубо говор€
					// а затем меньшее значение присваиваем переменной tmp->next
					// затем весь путь стэка после начального элемента записываем
					// в tmp->next->next
					Stack* tmp_for_swap = tmp->next->next;
					tmp->next->next = tmp_for_swap->next;
					tmp_for_swap->next = tmp->next;
					tmp->next = tmp_for_swap;
				}
			limit = tmp->next;
		} while (begin->next->next != limit);

		std::cout << "Done!\n";

		pop();
	}

	void SortNear() {
		Stack* limit = nullptr, *tmp, *t = begin;
		
		if (begin->next->next == nullptr) {
			std::cout << "SortNear: Stack is empty!\n";
			return;
		}

		std::cout << "SortNear: Sort of stack - ";
		
		for (; t->next != limit;) {
			for (tmp = t; tmp->next != limit; tmp = tmp->next) {
				if (tmp->info_ > tmp->next->info_) {
					int tmp_for_swap = tmp->info_;
					tmp->info_ = tmp->next->info_;
					tmp->next->info_ = tmp_for_swap;
				}
			}
			limit = tmp;
		}

		std::cout << "Done!\n";
	}

};

Stack*  FindMax(Stack **copy) {
	Stack* p = nullptr, *max = nullptr;

	p = (*copy)->GetBegin();
	max = (*copy)->GetBegin();

	while (p != nullptr) {
 
		if (p->GetInfo() > max->GetInfo()) {
			max = p;
		}

		p = p->GetNext();
	}

//	std::cout << "Max: " << max->GetInfo() << std::endl;
	return max;
}

Stack* CreateNewStack(Stack* (&old_stack), Stack* maximum) {
	Stack* old = new Stack;
	Stack* ref = new Stack;
	old = old_stack->GetBegin()->GetNext();

	while (old != maximum && old != nullptr) {
		ref->push(old->GetInfo());
		old = old->GetNext();
	}

	return ref;
}

void Test();

int main() {
	Stack* stack = new Stack;

	int n = 0;
	std::cout << "Input amount of elements: ";
	std::cin >> n;

	std::cout << "Input elements:\n";

	while (n--) {
		int tmp = 0;
		std::cin >> tmp;
		stack->push(tmp);
	}

	std::cout << "Default stack:\n";
	stack->view();

	// Create new stack from elements between BEGIN and MAX
	Stack* elements_from_old_stack = new Stack;
	elements_from_old_stack = CreateNewStack(stack, FindMax(&stack));

	// не знаю нужна очистка старого или нет?
	std::cout << "Stack between begin and max:\n";
	elements_from_old_stack->view();

	delete stack, elements_from_old_stack;
	return 0;
}

void Test() {
	Stack* stack = new Stack;

	stack->push(1);
	stack->push(2);
	stack->push(3);


	stack->view();
	std::cout << "\n";
	stack->SortAdress();
	stack->view();
	stack->push(90);
	stack->push(22131);
	stack->push(-1);
	stack->SortAdress();
	std::cout << std::endl;
	stack->view();
	stack->push(22134);
	stack->push(-2);
	stack->push(-3);
	stack->push(-5);

	//FindMax(&stack);
	Stack* elements_from_old_stack = new Stack;
	elements_from_old_stack = CreateNewStack(stack, FindMax(&stack));

	// не знаю нужно удаление старого или нет?
	elements_from_old_stack->view();

	delete stack, elements_from_old_stack;
}