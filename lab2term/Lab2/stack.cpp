#include "stack.h"

void Stack::push(int info) {
    Stack* tmp = new Stack(info);
    // Добавляю во временную переменную следующий элемент стэка, а затем делаю действия уже с основным стэком
    tmp->next = begin;
    next = begin;

    tmp->begin = new Stack();
    begin = tmp;
}

void Stack::pop(bool isNeedToPrintMessage) {
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
        if (isNeedToPrintMessage)
            std::cout << "Delete last element: Done!\n";
    }
    else if (isNeedToPrintMessage){
        std::cout << "Delete last element: stack is empty!\n";
    }
}

void Stack::view() {
    Stack* tmp = begin;
    bool first = true;

    std::cout << "Stack view: ";

    if (tmp == nullptr) {
        std::cout << "nothing to show :(";
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

void Stack::peek() {
    if (begin != nullptr) {
        std::cout << begin->info_ << std::endl;
    }
    else {
        std::cout << "Peek: stack is empty!\n";
    }
}

void Stack::clear(bool isNeedToPrintMessage) {

    // this != nullptr - плохо
    if (isNeedToPrintMessage && (this == nullptr || begin == nullptr))
        std::cout << "Nothing to clear!\n";
    else {
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
}

void Stack::Sort() {
    Stack* limit = nullptr, * tmp, * t = begin;

    if (begin == nullptr || begin->next == nullptr) {
        std::cout << "Sort: stack is empty!\n";
        return;
    }

    std::cout << "Sort: Sort of stack - ";
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