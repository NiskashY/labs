#include "individualTask.h"

int FindMax(Queue*& copy) {
    Queue* p = nullptr, * max = nullptr;

    p = copy->GetBegin();
    max = copy->GetBegin();

    if (p == nullptr) { // check if queue is empty
        throw std::runtime_error("No elements in queue\n");
    }

    while (p != nullptr) {

        if (p->GetInfo() > max->GetInfo()) {
            max = p;
        }

        p = p->GetNext();
    }

    //	std::cout << "Max: " << max->GetInfo() << std::endl;
    return max->GetInfo();
}