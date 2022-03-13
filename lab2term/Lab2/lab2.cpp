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
	Stack* begin = nullptr; // peek of Stack / or current element
public:

	explicit Stack(int i) { info_ = i; }

	Stack() = default;

	Stack* GetBegin() const{ return begin; }

	int GetInfo() const { return info_; }

	Stack* GetNext() const { return next; }

	// Funtions for working with stack

	void push(int info) {
        Stack *tmp = new Stack(info);
        // Добавляю во временную переменную следующий элемент стэка, а затем делаю действия уже с основным стэком
        tmp->next = begin;
        next = begin;

        tmp->begin = new Stack();
        begin = tmp;
    }

    void pop() {
        if (begin != nullptr) {
            Stack* tmp = begin;
            next = next->next;
            begin = begin->next;
            delete tmp;
        }
        else {
            std::cout << "Pop: stack is empty!\n";
        }
    }

	void view() {
		Stack* tmp = begin;
		bool first = true;

		std::cout << "View: ";

        if (tmp == nullptr) {
            std::cout << "stack is empty :(";
        }

		while (tmp != nullptr) {
			if (!first) {
				std::cout << ", ";
			}
			first = false;
			std::cout << tmp->info_;
			tmp = tmp->next;
		}

		std::cout << "\n";
	}

	void peek() {
		if (begin != nullptr) {
			std::cout << begin->info_ << std::endl;
		}
		else {
			std::cout << "Peek: stack is empty!\n";
		}
	}

	void clear(bool isNeedToPrintMessage = true) {

		while (begin != nullptr) {
			Stack* tmp = begin;
            begin = next;
            if (next != nullptr)
                next = begin->next;
            delete tmp;
            tmp = nullptr;
        }

        if (isNeedToPrintMessage)
            std::cout << "Clear: stack is empty!\n";
	}

	void SortAddress() {
		Stack* limit = nullptr, *tmp;

		if (begin->next->next == nullptr) {
			std::cout << "SortAddress: stack is empty!\n";
			return;
		}

		// Добавляем элемент, чтобы сортировка корректно работала, в конце его нужно удалить
		const int TMP_FOR_DELETE = -1;
		push(TMP_FOR_DELETE);

		std::cout << "SortAddress: stack is empty!\n";
		// 1 -> 4 -> 3 -> 0 -> nullptr
		// 1 -> 4 -> 0 -> nullptr
		// 1 ->
		do {
			for (tmp = begin; tmp->next->next != limit; tmp = tmp->next)
				if (tmp->next->info_ > tmp->next->next->info_) {
					// вы двигаем весь стек после элемента на вправо грубо говоря
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
			std::cout << "SortNear: stack is empty!\n";
			return;
		}

		std::cout << "SortNear: stack is empty!\n";

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

bool isMaximumBeginInvalid(Stack* (&stack), Stack* (&max)){
    const char* ERROR_MESSAGE = "New stack will be empty, because ";
    if (stack->GetBegin() == max) {
        std::cout << ERROR_MESSAGE << "Maximum = begin\n";
        return true;
    } else if (stack->GetBegin()->GetNext() == max) {
        std::cout << ERROR_MESSAGE << "No elements between maximum and begin\n";
        return true;
    }

    return false;
}

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
	Stack* old = new Stack();
	Stack* ref = new Stack();
    old = old_stack->GetNext();

    if (isMaximumBeginInvalid(old_stack, maximum)) {
        return ref;
    }

	while (old->GetNext() != nullptr && old != maximum) {
		ref->push(old->GetInfo());
		old = old->GetNext();
	}

    // очищаю для того, чтобы перевернуть stack
    old->clear(false);

    ref = ref->GetBegin();
    // тут ref, а нe ref->GetBegin(), т.к. я уже взял GetBegin(), а это значит, что когда на последнем шаге
    // будет ref->GetBegin() ( в это время ref = ref ->GetNext()  =  ref = nullptr) выскочит ошибка. из-за обращения к nullptr;
    while (ref != nullptr) {
        old->push(ref->GetInfo());
        ref = ref->GetNext();
    }

	return old;
}

void Test1();
void Test2();
void Test3();

/*

	если в цикле с пользователем есть break -> на continue

*/

int main() {
	//Test1();
    //Test2();
    Test3();
	return 0;
}

void Test1() {
	Stack* stack = new Stack();

    stack->view();

	stack->push(1);
	stack->push(2);
	stack->push(3);


    std::cout << "1: ";
    stack->view();

    stack->SortAddress();

    std::cout << "2: ";
    stack->view();

	stack->push(90);
	stack->push(22131);
    stack->push(-1);

    stack->SortAddress();
	std::cout << std::endl;

    stack->push(10000);
    stack->push(-2);
    stack->push(-3);
    stack->push(-5);

    std::cout << "3: ";
    stack->view();



    stack->SortAddress();
    std::cout << "4: ";
    stack->view();


	//FindMax(&stack);
	Stack* elements_from_old_stack = new Stack;
	elements_from_old_stack = CreateNewStack(stack, FindMax(&stack));

	// не знаю нужно удаление старого или нет?
    std::cout << "New Stack: \n";
    elements_from_old_stack->view();
    std::cout << "Old Stack: \n";
    stack->view();
	delete stack, elements_from_old_stack;

}

void Test2() {
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

    stack->view();
    std::cout << "\n";

    // Create new stack from elements between BEGIN and MAX
    Stack* elements_from_old_stack = new Stack;
    elements_from_old_stack = CreateNewStack(stack, FindMax(&stack));

    // не знаю нужна очистка старого или нет?
    std::cout << "Stack between begin and max:\n";
    elements_from_old_stack->view();

    delete stack, elements_from_old_stack;
}

void Test3() {
    Stack* stack = new Stack();


    // Валится на этом тесте 2 - 3 - 1 из-за clear
    stack->push(3);
    stack->push(1);
    stack->push(2);
    stack->push(3);
    stack->push(1);
    stack->push(2);
    stack->push(3);
    stack->push(1);
    stack->push(2);
    stack->push(3);
    stack->push(1);
    stack->push(2);
    stack->push(3);
    stack->push(1);
    stack->push(2);
    stack->push(3);
    stack->push(1);
    stack->push(2);

    stack->SortAddress();

    std::cout << "(Bef stack) ";
    stack->view();


    //FindMax(&stack);
    Stack* elements_from_old_stack = new Stack();
    elements_from_old_stack = CreateNewStack(stack, FindMax(&stack));

    // не знаю нужно удаление старого или нет?
    std::cout << "(New stack) ";
    elements_from_old_stack->view();
    std::cout << "(Old Stack) ";
    stack->view();
    stack->clear();
    stack->view();
    delete stack, elements_from_old_stack;

}