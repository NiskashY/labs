#include <iostream>
#include <iomanip>
#include "stack.h"
#include "individualTask.h"

/*
    Перенести из созданного списка в новый список все элементы,
    находящиеся между вершиной и максимальным элементом.
*/

void Test1();
void Test2();
void Test3();
void IndividualTask(Stack*&, bool isItTest = false);
void AddElements(Stack*&);
int CheckNum();

int main() {
    Stack* stack = new Stack();

    while (true) {
        system("cls");
        std::cout << "\t\tTask: move elements in new stack from begin - maximum\n\n";
        stack->view();
        std::cout << "\n0 - Run Tests.\n1 - Creat new stack.\n2 - Add.\n3 - Delete Last Element.\n4 - Clear.\n5 - Sort.\n6 - Individual Task.\nelse - Exit.\n\nYour choice : ";
        int choice = CheckNum();

        switch (choice) {
            case 0: {
                Test1();
                std::cout << "\n\n";
                Test2();
                std::cout << "\n\n";
                Test3();
                break;
            }
            case 1: case 2: {
                if (choice == 1 && stack->GetHead() != nullptr) {
                    std::cout << "Are you sure you want to delete not empty stack? 1 - y, else - n: ";
                    int tmp = CheckNum();
                    if (tmp != 1)
                        continue;
                    std::cout << "Old stack not empty -> deleting the old stack\n";
                    stack->clear();
                }
                AddElements(stack);
                std::cout << "The elements have been successfully added\n";
                break;
            }
            case 3: {
                stack->pop();
                break;
            }
            case 4: {
                stack->clear();
                break;
            }
            case 5: {
                stack->Sort();
                break;
            }
            case 6: {
                IndividualTask(stack);
                break;
            }
            default: {
                std::cout << "\n\t\t\tBye!\n";
                return 0;
            }
        }
        std::cout << '\n';
        system("pause");
    }
    return 0;
}

void IndividualTask(Stack*& stack, bool isItTest) {
    if (stack->GetHead() == nullptr) {
        std::cout << "Stack is empty!\n";
        return;
    }

    std::cout << "(Before dividing Stack) ";
    stack->view();

    Stack* new_stack = MoveElementsFromTo(stack, FindMax(stack));

    std::cout << std::left << std::setw(24) << "(New Stack) ";
    new_stack->view();
    std::cout << std::left << std::setw(24) << "(Old Stack) ";
    stack->view();

    if (!isItTest) {
        std::cout << "Do you want to assign a new_stack to an old_stack? (Yes - 1, No - else): ";
        int tmp = CheckNum();
        if (tmp == 1) {
            stack = new_stack;
        }
    }
}

void AddElements(Stack*& stack) {
    std::cout << "Input amount of numbers: ";
    int n = CheckNum();
    for (int i = 0; i < n; ++i) {
        std::cout << "#" << i + 1 << " Input Number : ";
        int number = CheckNum();
        stack->push(number);
    }
}

int CheckNum() {
    int var;

    while (!(scanf_s("%d", &var)) || std::cin.get() != '\n') {
        std::cout << "Error! Something go wrong ReEnter: ";
        std::cin.clear();
        while (std::cin.get() != '\n');
    }

    return var;
}

// ---------------tests-------------

void Test1() {
    std::cout << "-------TEST1----\n\n";

    Stack* stack = new Stack();
    stack->view();

    stack->push(1);
    stack->push(2);
    stack->push(3);


    std::cout << "1: ";
    stack->view();

    stack->Sort();
    std::cout << "2: ";
    stack->view();

    stack->push(90);
    stack->push(22131);
    stack->push(-1);

    stack->Sort();
    std::cout << "3: ";
    stack->view();

    stack->push(10000);
    stack->push(-2);
    stack->push(-3);
    stack->push(-5);

    std::cout << "4: ";
    stack->view();

    stack->Sort();
    std::cout << "5: ";
    stack->view();

    IndividualTask(stack, true);

    delete stack;
}

void Test2() {
    std::cout << "-------TEST2----\n\n";
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


    stack->Sort();

    std::cout << "(BefPop &ASor) ";
    stack->view();

    stack->pop();
    std::cout << "(AftPop stack) ";
    stack->view();

    IndividualTask(stack, true);

    stack->clear();
    stack->view();

    delete stack;

}

void Test3() {
    std::cout << "-------TEST3----\t(Random elements)\n\n";
    Stack* stack = new Stack;
    srand(time(0));
    int n = 10;

    while (n--) {
        int tmp = 0;
        tmp = rand() % 10 + 1;
        stack->push(tmp);
    }

    stack->view();
    std::cout << "\n";

    // Create new stack from elements between BEGIN and MAX
    IndividualTask(stack, true);

    delete stack;
}
