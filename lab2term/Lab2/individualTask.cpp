#include "individualTask.h"

bool isMaximumBeginInvalid(const Node* const& stack, const Node* const& max) {  // first const - for addres, second const - for value
    const char* kErrorMsg = "New stack will be empty, because ";
    const char* kMaxEqualBegin = "Maximum = Head";
    const char* kNoElements = "No elements between Maximum and Head";

    if (stack == max) {
        std::cout << "\n\t\t" << kErrorMsg << kMaxEqualBegin << "\n\n";
        return true;
    }
    else if (stack->next == max) {
        std::cout << "\n\t\t" << kErrorMsg << kNoElements << "\n\n";
        return true;
    }

    return false;
}

Node* FindMax(Stack*& stack) {
    Node* stack_head = stack->GetHead();
    Node* max_node = stack_head;

    while (stack_head) {
        if (stack_head->info_ > max_node->info_) {
            max_node = stack_head;
        }
        stack_head = stack_head->next;
    }

     return max_node;
}

void NewReverseStack(Stack* (&old), Stack* (&destination), const Node*const& (maximum) = nullptr) {

    while (old->GetHead()) {  // old/*->GetNext()*/ != nullptr /*&& old->GetBegin() != nullptr*/
        if (maximum && old->GetInfo() == maximum->info_) {
            break;
        }
        destination->push(old->GetInfo());
        old->pop(false);
    }

}

Stack* MoveElementsFromTo(Stack*& old_stack, const Node* const& maximum) { // old - copy of stack
    // Создаю две переменные, чтобы stack получился не вверх ногами.
    
    // Изначально result = nullptr, чтобы вернуть это из функции, если нет элементов для Task
    Stack* reverse_tmp = new Stack();
    Stack* result = new Stack();
    if (isMaximumBeginInvalid(old_stack->GetHead(), maximum)) {
        return result;
    }



    Node* old_head = old_stack->GetHead();
    old_stack->SetHead(old_stack->GetNext()); // go to the next element (begin -> element after begin), because of task

    NewReverseStack(old_stack, reverse_tmp, maximum);
    NewReverseStack(reverse_tmp, result);
    old_stack->push(old_head->info_);

    return result;
}
