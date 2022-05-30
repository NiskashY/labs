#pragma once

#include <iostream>

enum class Direction {
    FRONT,
    BACK
};

void SwapViewDirection(Direction&);

struct Node {
    int info_ = 0;
    Node* prev = nullptr;
    Node* next = nullptr;

    Node() = default;

    Node(const int& info) : info_(info) {}

    Node* GetDestinationNode(const Direction&); // get next or prev node (depends from paramentr direction).
};

void ConnectNextPrevNodes(Node*&); // connect next and prev nodes

class Queue {   // double linked list
private:
    Node* head = nullptr;   // beginning of the queue
    Node* tail = nullptr;   // end of the queue

public:

    Queue() = default;

    explicit Queue(const int& info) {
        head = new Node();
        head->info_ = info; 
        tail = head;    // tail and head point to the same element when creating
    }

    int GetInfo() const { return head->info_; }
    Node* GetHead() const { return head; }
    Node* GetNext() const { return head->next; }
    Node* GetPrev() const { return head->prev; }
    Node* GetTail() const { return tail; }

    // Funtions for working with queue

    void push_back(const int& info);
    void push_front(const int& info);
    void pop_front(bool isNeedToPrintMessage = true);
    void pop_back(bool isNeedToPrintMessage = true);
    void pop(const int& element, bool isNeedToPrintMessage = true);
    void view(const Direction& direction = Direction::FRONT);
    void peek();
    void clear(bool isNeedToPrintMessage = true);
    void sort();
    bool empty() const;

};

void ShowViewHeader(const Direction&, const Node* const);
