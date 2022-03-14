#pragma once
#include <iostream>

class Stack {
private:
    int info_ = 0; // information
    Stack* next = nullptr; // next element
    Stack* begin = nullptr; // peek of Stack / or current element
public:

    explicit Stack(int i) { info_ = i; }

    Stack() = default;

    Stack* GetBegin() const { return begin; }

    int GetInfo() const { return info_; }

    Stack* GetNext() const { return next; }

    // Funtions for working with stack

    void push(int info);
    void pop(bool isNeedToPrintMessage = true);
    void view();
    void peek();
    void clear(bool isNeedToPrintMessage = true);
    void Sort();

};