#pragma once
#include <iostream>

template<class T = int>
class Stack {
private:
    T info_ = 0; // information
    Stack<T>* next = nullptr; // next element
    Stack<T>* begin = nullptr; // peek of Stack / or current element
public:

    explicit Stack<T>(T i) { info_ = i; }

    Stack<T>() = default;

    Stack<T>* GetBegin() const { return begin; }

    T GetInfo() const { return info_; }

    Stack<T>* GetNext() const { return next; }

    // Funtions for working with stack

    void push(T info) {
        Stack<T>* tmp = new Stack(info);
        // Добавляю во временную переменную следующий элемент стэка, а затем делаю действия уже с основным стэком
        tmp->next = begin;
        next = begin;

        tmp->begin = new Stack();
        begin = tmp;
    }

    void pop(bool isNeedToPrintMessage = false) {
        if (begin != nullptr) {
            Stack<T>* tmp1 = begin;
            Stack<T>* tmp2 = next;
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
        else if (isNeedToPrintMessage) {
            std::cout << "Delete last element: stack is empty!\n";
        }
    }

    void view() {
        Stack<T>* tmp = begin;
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

    T peek() {
        if (begin != nullptr) {
            return begin->info_;
        }
        return '{';
    }

    bool empty() {
        return begin == nullptr;
    }

    void clear(bool isNeedToPrintMessage = false) {
        // this != nullptr - плохо
        if (isNeedToPrintMessage && (this == nullptr || begin == nullptr))
            std::cout << "Nothing to clear!\n";
        else {
            while (this != nullptr && begin != nullptr) {
                Stack<T>* tmp = begin;
                begin = next;
                if (next != nullptr)
                    next = begin->next;
                delete tmp;
            }

            if (isNeedToPrintMessage)
                std::cout << "Clear: now stack is empty!\n";
        }
    }

    void Sort() {
        Stack<T>* limit = nullptr, * tmp, * t = begin;

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

};