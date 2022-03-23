#include "queue.h"

void Queue::push_front(int info) {
    Queue* tmp = new Queue(info);
    // �������� �� ��������� ���������� ��������� ������� �����, � ����� ����� �������� ��� � �������� ������
    if (end == nullptr) {

        tmp->next = begin;
        tmp->prev = nullptr;
        tmp->begin = new Queue();
        
        next = begin;
        begin = end = tmp;
    }
    else {
        begin->prev = tmp;

        tmp->end = end;
        tmp->next = begin;
        tmp->prev = nullptr;
        tmp->begin = new Queue();
        
        next = begin;
        begin = tmp;
    }
}

void Queue::push_back(int info) {
    Queue* tmp = new Queue(info);
    // �������� �� ��������� ���������� ��������� ������� �����, � ����� ����� �������� ��� � �������� ������
    if (end == nullptr) {
        tmp->next = begin;
        tmp->prev = nullptr;
        next = begin;

        tmp->begin = new Queue();
        begin = end = tmp;
    }
    else {
        tmp->next = nullptr;
        tmp->prev = end;
        tmp->begin = new Queue();

        // ����������� end->next = tpm, ����� �� �������� �������, 
        // � ����� � end'a ������������� ��������� �����
        end->next = tmp;
        end = end->next;
    }
}


void Queue::pop(bool isNeedToPrintMessage) {
    if (begin != nullptr) {
        Queue* tmp1 = begin;
        Queue* tmp2 = next;
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
        std::cout << "Delete last element: queue is empty!\n";
    }
}

void Queue::view() {
    Queue* tmp = begin;
    bool first = true;

    std::cout << "Queue view: ";

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

void Queue::peek() {
    if (begin != nullptr) {
        std::cout << begin->info_ << std::endl;
    }
    else {
        std::cout << "Peek: queue is empty!\n";
    }
}

void Queue::clear(bool isNeedToPrintMessage) {

    // this != nullptr - �����
    if (isNeedToPrintMessage && (this == nullptr || begin == nullptr))
        std::cout << "Nothing to clear!\n";
    else {
        while (this != nullptr && begin != nullptr) {
            Queue* tmp = begin;
            begin = next;
            if (next != nullptr)
                next = begin->next;
            delete tmp;
        }

        if (isNeedToPrintMessage)
            std::cout << "Clear: now queue is empty!\n";
    }
}

void Queue::Sort() {
    Queue* limit = nullptr, * tmp, * t = begin;

    if (begin == nullptr || begin->next == nullptr) {
        std::cout << "Sort: queue is empty!\n";
        return;
    }

    std::cout << "Sort: Sort of queue - ";
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