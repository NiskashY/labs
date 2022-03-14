#include "individualTask.h"

bool isMaximumBeginInvalid(Stack* (&stack), Stack* (&max)) {
    const char* ERROR_MESSAGE = "New stack will be empty, because ";
    if (stack->GetBegin() == max) {
        std::cout << ERROR_MESSAGE << "Maximum = begin or no elements in the stack\n";
        return true;
    }
    else if (stack->GetBegin()->GetNext() == max) {
        std::cout << ERROR_MESSAGE << "No elements between maximum and begin\n";
        return true;
    }

    return false;
}

Stack* FindMax(Stack** copy) {
    Stack* p = nullptr, * max = nullptr;

    p = (*copy)->GetBegin();
    max = (*copy)->GetBegin();

    while (p != nullptr) {

        if (p->GetInfo() > max->GetInfo()) {
            max = p;
        }

        p = p->GetNext();
    }

    //	std::cout << "Max: " << max->GetInfo() << std::endl;
    return max;
}

void NewReverseStack(Stack* (&old), Stack* (&ref), Stack* (maximum) = nullptr) {

    while (old/*->GetNext()*/ != nullptr && old->GetBegin() != nullptr) {
        if (maximum != nullptr && old->GetInfo() == maximum->GetInfo()) {
            break;
        }
        ref->push(old->GetInfo());
        old->pop(false);
    }

}

Stack* MoveElementsFromTo(Stack* (&old_), Stack* maximum) {
    // —оздаю две переменные, чтобы stack получилс€ не вверх ногами. Ќе могу использовать повторно old, т.к. это вли€ет на основной stack
    Stack* reverse_tmp = new Stack();
    Stack* result = new Stack();


    if (isMaximumBeginInvalid(old_, maximum)) {
        return result;
    }

    Stack* old = old_->GetNext();
    NewReverseStack(old, reverse_tmp, maximum);

    reverse_tmp = reverse_tmp->GetBegin();
    NewReverseStack(reverse_tmp, result);


    return result;
    /*
    Some tests

    std::cout << "(Old_st in cns Stack 1) ";
    old_stack->view();
    std::cout << "(Old_st in cns Stack 2) ";
    old_stack->view();
    std::cout << "(Old_st in cns Stack 3) ";
    old_stack->view();
    std::cout << "(NewOld in cns Stack 4) ";
    old->view();
    std::cout << "(NewU   in cns Stack 5) ";
    result->view();

*/
}
