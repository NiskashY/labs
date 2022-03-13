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
            Stack* tmp1 = begin;
            Stack* tmp2 = next;
            begin = next;

            if (next != nullptr) {
                info_ = next->info_;
                next = next->next;
            }

            delete tmp1, tmp2;
            tmp1 = tmp2 = nullptr;
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

        // this != nullptr - плохо
		while (this != nullptr && begin != nullptr) {
			Stack* tmp = begin;
            begin = next;
            if (next != nullptr)
                next = begin->next;
            delete tmp;
        }

        if (isNeedToPrintMessage)
            std::cout << "Clear: now stack is empty!\n";
	}

	void SortAddress() {
        // Криво работает ON NE RABOTAET
		Stack* limit = nullptr, *tmp;

		if (begin->next->next == nullptr) {
			std::cout << "SortAddress: stack is empty!\n";
			return;
		}

		// Добавляем элемент, чтобы сортировка корректно работала, в конце его нужно удалить
		const int TMP_FOR_DELETE = -1;
		push(TMP_FOR_DELETE);

		std::cout << "SortAddress: Sort of stack - ";
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

		if (begin == nullptr || begin->next == nullptr) {
			std::cout << "SortNear: stack is empty!\n";
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

bool isMaximumBeginInvalid(Stack* (&stack), Stack* (&max)){
    const char* ERROR_MESSAGE = "New stack will be empty, because ";
    if (stack->GetBegin() == max) {
        std::cout << ERROR_MESSAGE << "Maximum = begin or no elements in the stack\n";
        return true;
    } else if (stack->GetBegin()->GetNext() == max) {
        std::cout << ERROR_MESSAGE << "No elements between maximum and begin\n";
        return true;
    }

    return false;
}

Stack* FindMax(Stack **copy) {
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

void NewReverseStack(Stack* (&old), Stack* (&ref), Stack* (maximum) = nullptr) {
    while (old/*->GetNext()*/ != nullptr && old->GetBegin() != nullptr ) {

        if (maximum != nullptr && old->GetInfo() == maximum->GetInfo()){
            break;
        }
        ref->push(old->GetInfo());
        old->pop();
    }

}

Stack* MoveElementsFromTo(Stack* (&old_), Stack* maximum) {
    // Создаю две переменные, чтобы stack получился не вверх ногами. Не могу использовать повторно old, т.к. это влияет на основной stack
    Stack* reverse_tmp = new Stack();
    Stack* result = new Stack();


    if (isMaximumBeginInvalid(old_, maximum)) {
        return result;
    }

    Stack* old = old_->GetNext();
    NewReverseStack(old, reverse_tmp, maximum);

    reverse_tmp = reverse_tmp->GetBegin();
    NewReverseStack(reverse_tmp, result);


	return result;
    /*
    Some tests

    std::cout << "(Old_st in cns Stack 1) ";
    old_stack->view();
    std::cout << "(Old_st in cns Stack 2) ";
    old_stack->view();
    std::cout << "(Old_st in cns Stack 3) ";
    old_stack->view();
    std::cout << "(NewOld in cns Stack 4) ";
    old->view();
    std::cout << "(NewU   in cns Stack 5) ";
    result->view();

*/
}

void Test1();
void Test2();
void Test3();

/*

	если в цикле с пользователем есть break -> на continue

*/

int main() {
    Test1();
    std::cout << "\n\n";
    //Test2();
    Test3();
	return 0;
}

void Test1() {
    std::cout << "-------TEST1----\n\n";

	Stack* stack = new Stack();
    stack->view();

	stack->push(1);
	stack->push(2);
	stack->push(3);


    std::cout << "1: ";
    stack->view();

    stack->SortNear();
    std::cout << "2: ";
    stack->view();

	stack->push(90);
	stack->push(22131);
    stack->push(-1);

    stack->SortNear();
    std::cout << "3: ";
    stack->view();


    stack->push(10000);
    stack->push(-2);
    stack->push(-3);
    stack->push(-5);

    std::cout << "4: ";
    stack->view();

    stack->SortNear();
    std::cout << "5: ";
    stack->view();



	Stack* elements_from_old_stack = MoveElementsFromTo(stack, FindMax(&stack));

    std::cout << "(New Stack) ";
    elements_from_old_stack->view();
    std::cout << "(Old Stack) ";
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
    elements_from_old_stack = MoveElementsFromTo(stack, FindMax(&stack));

    // не знаю нужна очистка старого или нет?
    std::cout << "Stack between begin and max:\n";
    elements_from_old_stack->view();

    delete stack, elements_from_old_stack;
}

void Test3() {
    std::cout << "-------TEST3----\n\n";
    Stack* stack = new Stack();


    stack->push(3);
    stack->push(1);
    stack->push(2);

    stack->push(3);
    stack->push(1);
    stack->push(2);

    stack->push(3);
    stack->push(1);
    stack->push(2);

//    stack->push(3);
//    stack->push(1);
//    stack->push(2);
//    stack->push(3);
//    stack->push(1);
//    stack->push(2);
//    stack->push(3);
//    stack->push(1);
//    stack->push(2);
    std::cout << "(After push) ";
    stack->view();


    stack->SortNear();

    std::cout << "(BefPop &ASor) ";
    stack->view();

    stack->pop();
    std::cout << "(AftPop stack) ";
    stack->view();

    Stack* elements_from_old_stack = new Stack();
    elements_from_old_stack = MoveElementsFromTo(stack, FindMax(&stack));


    std::cout << "(New stack) ";
    elements_from_old_stack->view();
    std::cout << "(Old Stack) ";
    stack->view();

    stack->clear();
    stack->view();

    delete stack, elements_from_old_stack;

}
