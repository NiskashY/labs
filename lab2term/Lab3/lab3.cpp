#include <iostream>
#include <iomanip>
#include "queue.h"
#include "tests.h"
/*
    Перенести из созданного списка в новый список все элементы,
    находящиеся между вершиной и максимальным элементом.
*/

void Push(Queue*&);
void Delete(Queue*&);
void View(Queue*&);

void (Queue::*Operation(Direction& direction))(int);
void AddElements(Queue*&, Direction&);
int CheckNum();

int main() {
    Queue* queue = new Queue();

    while (true) {
        //  Front->Back.\n5 - View Back->Front
        system("cls");
        const char MENU[] = "\t\tTask: move elements in new queue from begin - maximum\n0 - Run Tests.\n1 - Creat new queue.\n2 - Push Front. \
            \n3 - Push Back.\n4 - View.\n5 - Pop element.\n6 - Clear.\n7 - Sort. \
            \n8 - Individual Task.\nelse - Exit.\n\nYour choice : ";

        std::cout << MENU;

        int choice = CheckNum();

        switch (choice) {
            case 0: {                

                Test5();
                /* 
               Test1();
                std::cout << "\n\n";
                Test2();
                std::cout << "\n\n";
                Test3();
                std::cout << "\n\n";
                Test4();
                */
                break;
            }
            case 1: case 2: case 3: {
                if (choice == 1 && queue->GetBegin() != nullptr) {
                    std::cout << "Are you sure you want to delete not empty queue? 1 - y, else - n: ";
                    int tmp = CheckNum();
                    if (tmp != 1)
                        continue;
                    std::cout << "Old queue not empty -> deleting the old queue\n";
                    queue->clear();
                }
                auto type = (choice == 2 ? Direction::FRONT : Direction::BACK);
                AddElements(queue, type);
                std::cout << "The elements have been successfully added\n";
                break;
            }
            case 4: {
                system("cls");
                std::cout << "\t\tTask: move elements in new queue from begin - maximum\n1 - View Front->Back.\n2 - View Back->Front\nelse - back.\nYour Choice: ";
                int choice = CheckNum();

                if (choice == 1)
                    queue->view();
                else if (choice == 2)
                    queue->reverse_view();
                else
                    continue;

                break;
            }
            case 5: {
                system("cls");
                std::cout << "\t\tTask: move elements in new queue from begin - maximum\n1 - Delete first element.\n2 - Delete last element.\
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
                else
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
                //IndividualTask(queue);
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

int CheckNum() {
    int var;

    while (!(scanf_s("%d", &var)) || std::cin.get() != '\n') {
        std::cout << "Error! Something go wrong ReEnter: ";
        std::cin.clear();
        while (std::cin.get() != '\n');
    }

    return var;
}


void Push(Queue*&) {

}

void Delete(Queue*&) {

}

void View(Queue*&) {

}