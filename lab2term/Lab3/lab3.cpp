#include <iostream>
#include <iomanip>
#include "queue.h"
/*
    Перенести из созданного списка в новый список все элементы,
    находящиеся между вершиной и максимальным элементом.
*/

enum class Direction {
    FRONT,
    BACK
};

void Test1();
void Test2();
void Test3();
void AddElements(Queue*&, Direction&);
void (Queue::*Operation(Direction& direction))(int);
int CheckNum();

int main() {
    Queue* queue = new Queue();

    while (true) {
        system("cls");
        std::cout << "\t\tTask: move elements in new queue from begin - maximum\n0 - Run Tests.\n1 - Creat new queue.\n2 - Push Front.\n3 - Push Back.\n4 - View.\n5 - Delete Last Element.\n6 - Clear.\n7 - Sort.\n8 - Individual Task.\nelse - Exit.\n\nYour choice: ";
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
                queue->view();
                break;
            }
            case 5: {
                queue->pop();
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

// ---------------tests-------------

void Test1() {
    std::cout << "-------TEST1----\n\n";

    Queue* queue = new Queue();
    queue->view();


    queue->push_back(4);
    queue->push_back(3);
    queue->push_back(2);
    queue->push_front(1);

    std::cout << "1: ";
    queue->view();

    queue->Sort();
    std::cout << "2: ";
    queue->view();

    queue->push_front(90);
    queue->push_front(22131);
    queue->push_front(-1);

    queue->Sort();
    std::cout << "3: ";
    queue->view();

    queue->push_back(10000);
    queue->push_front(-2);
    queue->push_back(-3);
    queue->push_front(-5);

    std::cout << "4: ";
    queue->view();

    queue->Sort();
    std::cout << "5: ";
    queue->view();

    delete queue;
}

void Test2() {
    std::cout << "-------TEST2----\n\n";
    Queue* queue = new Queue();


    queue->push_front(3);
    queue->push_front(1);
    queue->push_front(2);

    queue->push_front(3);
    queue->push_front(1);
    queue->push_front(2);

    queue->push_front(3);
    queue->push_front(1);
    queue->push_front(2);

    //    queue->push_front(3);
    //    queue->push_front(1);
    //    queue->push_front(2);
    //    queue->push_front(3);
    //    queue->push_front(1);
    //    queue->push_front(2);
    //    queue->push_front(3);
    //    queue->push_front(1);
    //    queue->push_front(2);
    std::cout << "(After push_front) ";
    queue->view();


    queue->Sort();

    std::cout << "(BefPop &ASor) ";
    queue->view();

    queue->pop();
    std::cout << "(AftPop queue) ";
    queue->view();



    queue->clear();
    queue->view();

    delete queue;

}

void Test3() {
    std::cout << "-------TEST3----\t(Random elements)\n\n";
    Queue* queue = new Queue;
    srand(time(0));
    int n = 10;

    while (n--) {
        int tmp = 0;
        tmp = rand() % 10 + 1;
        queue->push_front(tmp);
    }

    queue->view();
    std::cout << "\n";

    // Create new queue from elements between BEGIN and MAX

    delete queue;
}
