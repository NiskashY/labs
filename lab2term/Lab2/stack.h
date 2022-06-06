#pragma once
#include <iostream>

struct Node {
    int info_ = 0;
    Node* next = nullptr;

    Node() = default;

    Node(const int& info) : info_(info) {}

};

class Stack {
private:
    Node* head = nullptr;

public:

    Stack() = default;

    explicit Stack(const int& info) { 
        if (!head) {
            head = new Node();
        }
        head->info_ = info; 
    }

    // this const does not change the data in new_head ->
    // -> we can provide arguments like nullptr by cosnt reference
    void SetHead(Node* const& new_head) { 
        head = new_head;
    }

    Node* GetHead() const { return head; }

    int GetInfo() const { return head->info_; }

    Node* GetNext() const { return head->next; }

    // Funtions for working with stack

    void push(const int& info);
    void pop(bool isNeedToPrintMessage = true);
    void view();
    void peek();
    void clear(bool isNeedToPrintMessage = true);
    void sort();
    void reverse();

};