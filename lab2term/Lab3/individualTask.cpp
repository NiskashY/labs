#include "individualTask.h"

int FindMax(Queue*& copy) {
    Queue* p = nullptr, * max = nullptr;

    p = copy->GetBegin();
    max = copy->GetBegin();

    while (p != nullptr) {

        if (p->GetInfo() > max->GetInfo()) {
            max = p;
        }

        p = p->GetNext();
    }

    //	std::cout << "Max: " << max->GetInfo() << std::endl;
    return max->GetInfo();
}