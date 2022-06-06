#include "stack.h"

void Stack::push(const int& info) {
    Node* node_new = new Node(info);
    node_new->next = head;
    head = node_new;

}

void Stack::pop(bool isNeedToPrintMessage) {
    if (head != nullptr) {
        Node* old_head_node = head;
        head = head->next;

        delete old_head_node;
        old_head_node = nullptr;

        if (isNeedToPrintMessage)
            std::cout << "Delete last element: Done!\n";
    }
    else if (isNeedToPrintMessage){
        std::cout << "Delete last element: stack is empty!\n";
    }
}

void Stack::view() {
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

void Stack::peek() {
    if (head) {
        std::cout << head->info_ << std::endl;
    }
    else {
        std::cout << "Peek: stack is empty!\n";
    }
}

void Stack::clear(bool isNeedToPrintMessage) {
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

void Stack::sort() {
    if (!head) {
        std::cout << "sort: stack is empty!\n";
        return;
    }

    Node* limit = nullptr;
    Node* tmp = nullptr;
    Node* t = head;

    std::cout << "sort: sort of stack - ";
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

void Stack::reverse() {
    Node* node_prev = nullptr;
    Node* node_next = nullptr;

    while (head) {
        node_next = head->next;
        head->next = node_prev;
        node_prev = head;
        if (!node_next) {
            break;
        }
        head = node_next;
    }
}