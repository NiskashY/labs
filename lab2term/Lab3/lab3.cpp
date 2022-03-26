#include <iostream>
#include <iomanip>
#include "queue.h"
#include "tests.h"
#include "individualTask.h"

/*
    В созданном списке определить максимальное значение и удалить его.
*/

void Push(Queue*&, int);
bool Pop(Queue*&);
void RunTests();
void (Queue::*Operation(Direction& direction))(int);
void AddElements(Queue*&, Direction&);
int CheckNum();

int main() {
    Queue* queue = new Queue();

    while (true) {
        system("cls");

        queue->view(); // это просто чтобы удобнее работать с меню было :D
        
        const char MENU[] = "\t\tTask: delete max element from queue.\n0 - Run Tests.\n1 - Creat new queue.\n2 - Push Front. \
            \n3 - Push Back.\n4 - Reverse View.\n5 - Pop element.\n6 - Clear.\n7 - Sort. \
            \n8 - Individual Task.\nelse - Exit.\n\nYour choice : ";

        std::cout << MENU;

        int choice = CheckNum();

        switch (choice) {
            case 0: {
                RunTests();
                break;
            }
            case 1: case 2: case 3: {
                Push(queue, choice);
                break;
            }
            case 4: {
                queue->reverse_view();
                break;
            }
            case 5: {
                // Чтобы не срабатывало system("pause"), если захотел вернуться на предыдущий шаг.
                if (!Pop(queue))
                    continue;

                break;
            }
            case 6: {
                queue->clear();
                break;
            }
            case 7: {
                queue->Sort();
                break;
            }
            case 8: {
                queue->pop(FindMax(queue));
                break;
            }
            default: {
                std::cout << std::setw(50) << std::right << "Bye!\n";
                return 0;
            }
        }
        std::cout << '\n';
        system("pause");
    }
    return 0;
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

// тут без & низя | создаю указатель на метод класса.
// а вообще тут можно просто через if, но тогда это не весело :)
void (Queue::*Operation(Direction& direction))(int) {
    return (direction == Direction::FRONT ? &Queue::push_front : &Queue::push_back);
}

void AddElements(Queue*& queue, Direction& direction) {
    std::cout << "Input amount of numbers: ";
    int n = CheckNum();
    for (int i = 0; i < n; ++i) {
        std::cout << "#" << std::setw(2) << std::left << i + 1 << " Input Number : ";
        int number = CheckNum();

        void (Queue::*operation)(int num);
        operation = Operation(direction);
        (queue->*operation)(number);
    }
}

void Push(Queue*& queue, int choice) {
    if (choice == 1 && queue->GetBegin() != nullptr) {
        std::cout << "Are you sure you want to delete not empty queue? 1 - y, else - n: ";
        int tmp = CheckNum();
        if (tmp != 1)
            return;
        std::cout << "Old queue not empty -> deleting the old queue\n";
        queue->clear();
    }
    auto type = (choice == 2 ? Direction::FRONT : Direction::BACK);
    AddElements(queue, type);
    std::cout << "The elements have been successfully added\n";
}

bool Pop(Queue*& queue) {
    system("cls");
    std::cout << "\t\tTask: delete max element from queue.\n1 - Delete first element.\n2 - Delete last element.\
                               \n3 - Delete element.\nelse - back.\nYour Choice: ";
    int choice = CheckNum();

    if (choice == 1)
        queue->pop_front();
    else if (choice == 2)
        queue->pop_back();
    else if (choice == 3) {
        std::cout << "Input element you want to delete: ";
        int element = CheckNum();
        queue->pop(element);
    }
    else {
        return false;
    }

    return true;
}

void RunTests() {
    Test1();
    std::cout << "\n\n";
    Test2();
    std::cout << "\n\n";
    Test3();
    std::cout << "\n\n";
    Test4();
    std::cout << "\n\n";
    Test5();
}