#include "menu_functions.h"


// тут без & низя | создаю указатель на метод класса.
// а вообще тут можно просто через if, но тогда это не весело :)
void (Queue::* Operation(Direction& direction))(const int&) {
    return (direction == Direction::FRONT ? &Queue::push_front : &Queue::push_back);
}

void AddElements(Queue& queue, Direction& direction) {
    std::cout << "Input amount of numbers: ";

    int n = 0;
    do {
        n = CheckNum();
    } while (!isNCorrect(n));

    for (int i = 0; i < n; ++i) {
        std::cout << "#" << std::setw(2) << std::left << i + 1 << " Input Number : ";
        int number = CheckNum();

        void (Queue:: * operation)(const int& num);
        operation = Operation(direction);
        (queue.*operation)(number);
    }
}

void Push(Queue& queue, int choice) {
    if (choice == 1 && !queue.empty()) {
        std::cout << "Are you sure you want to delete not empty queue? 1 - y, else - n: ";
        int tmp = CheckNum();
        if (tmp != 1)
            return;
        std::cout << "Old queue not empty -> deleting the old queue\n";
        queue.clear();
    }
    auto type = (choice == 2 ? Direction::FRONT : Direction::BACK);
    AddElements(queue, type);
    std::cout << "The elements have been successfully added\n";
}

bool Pop(Queue& queue) {
    system("cls");
    const char* const kTask = "\t\tTask: delete max element from queue";
    const char* const kMenu = "1 - Delete first element.\n2 - Delete last element.\
                               \n3 - Delete element.\nelse - back.\nYour Choice: ";
    std::cout << kTask << "\n\n";
    queue.view();
    std::cout << "\n" << kMenu;
    int choice = CheckNum();

    if (choice == 1)
        queue.pop_front();
    else if (choice == 2)
        queue.pop_back();
    else if (choice == 3) {
        std::cout << "Input element you want to delete: ";
        int element = CheckNum();
        queue.pop(element);
    }
    else {
        return false;
    }

    return true;
}

void ShowMenuHeader(Queue& queue, const Direction& view_direction) {
    const char kMenu[] = "0 - Run Tests.\n1 - Create new queue.\n2 - Push Front. \
            \n3 - Push Back.\n4 - Change view direction.\n5 - Pop element.\n6 - Clear.\n7 - Sort. \
            \n8 - Individual Task.\nelse - Exit.\n\nYour choice : ";
    const char kTask[] = "\t\tTask: delete max element from queue.";
    std::cout << kTask << "\n\n";
    queue.view(view_direction); // это просто чтобы удобнее работать с меню было :D
    std::cout << "\n" << kMenu;

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

bool isNCorrect(int& n) {
    if (n <= 0) {
        std::cout << "Can't add <= 0 elements! ReEnter: ";
    }
    return n > 0;
}
