#pragma once
#include <iostream>

template<class T>
struct Node {
    Node* next = nullptr;
    T info_ = 0;

    Node() = default;

    Node(const T& info) : info_(info) {}

};

template<class T>
class Stack {
private:
    Node<T>* head = nullptr;

public:

    Stack() = default;

    explicit Stack(const T& info) {
        if (!head) {
            head = new Node();
        }
        head->info_ = info;
    }

    // this const does not change the data in new_head ->
    // -> we can provide arguments like nullptr by cosnt reference
    void SetHead(Node<T>* const& new_head) {
        head = new_head;
    }

    Node<T>* GetHead() const { return head; }

    T GetInfo() const { return head->info_; }

    Node<T>* GetNext() const { return head->next; }
    
    // Funtions for working with stack
    
    bool empty() {
        return head == nullptr;
    }

    void push(const T& info) {
        Node<T>* node_new = new Node<T>(info);
        node_new->next = head;
        head = node_new;
    }

    void pop(bool isNeedToPrintMessage = false) {
        if (head != nullptr) {
            Node<T>* old_head_node = head;
            head = head->next;

            delete old_head_node;
            old_head_node = nullptr;

            if (isNeedToPrintMessage)
                std::cout << "Delete last element: Done!\n";
        }
        else if (isNeedToPrintMessage) {
            std::cout << "Delete last element: stack is empty!\n";
        }
    }

    void view() {
        Node* tmp_head = head;
        bool first = true;

        std::cout << "Stack view: ";

        if (tmp_head == nullptr) {
            std::cout << "nothing to show :(";
        }

        while (tmp_head != nullptr) {
            if (!first) {
                std::cout << ", ";
            }
            first = false;

            std::cout << tmp_head->info_;
            tmp_head = tmp_head->next;
        }

        std::cout << "\n";
    }

    T peek() {
        if (head) {
            return head->info_;
        }
        return {};
    }

    void clear(bool isNeedToPrintMessage = false) {
        if (!head && isNeedToPrintMessage) {
            std::cout << "Nothing to clear!\n";
        }
        else if (head) {
            while (head) {  // while stack not empty
                pop(false);
            }

            if (isNeedToPrintMessage)
                std::cout << "Clear: now stack is empty!\n";
        }
    }

};


