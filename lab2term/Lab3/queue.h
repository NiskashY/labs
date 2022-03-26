#pragma once

#include <iostream>

enum class Direction {
    FRONT,
    BACK
};

class Queue {
private:
    int info_ = 0; // information

    Queue* end = nullptr; // last element
    Queue* begin = nullptr; // peek of Queue / or current element
    Queue* prev = nullptr; // prev element
    Queue* next = nullptr; // next element

public:

    explicit Queue(int i) { info_ = i; }

    Queue() = default;

    int GetInfo() const { return info_; }
    
    Queue* GetBegin() const { return begin; }
    
    Queue* GetNext() const { return next; }
    
    Queue* GetEnd() const { return end; }

    // Funtions for working with queue

    void push_back(int info);
    void push_front(int info);
    void pop_front(bool isNeedToPrintMessage = true);
    void pop_back(bool isNeedToPrintMessage = true);
    void pop(int element, bool isNeedToPrintMessage = true);
    void view();
    void reverse_view();
    void peek();
    void clear(bool isNeedToPrintMessage = true);
    void Sort();

};