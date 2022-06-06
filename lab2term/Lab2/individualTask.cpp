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

void GetStackBetweenBeginMaximum(Stack* (&old), Stack* (&destination), const Node*const& (maximum) = nullptr) {

    while (old->GetHead()) {  // old/*->GetNext()*/ != nullptr /*&& old->GetBegin() != nullptr*/
        if (maximum && old->GetInfo() == maximum->info_) {
            break;
        }
        destination->push(old->GetInfo());
        old->pop(false);
    }
    destination->reverse();
}

Stack* MoveElementsFromTo(Stack*& old_stack, const Node* const& maximum) { // old - copy of stack
    // Изначально result = nullptr, чтобы вернуть это из функции, если нет элементов для Task
    
    Stack* result = new Stack();
    if (isMaximumBeginInvalid(old_stack->GetHead(), maximum)) {
        return result;
    }

    Node* old_head = old_stack->GetHead();
    old_stack->SetHead(old_stack->GetNext()); // go to the next element (begin -> element after begin), because of task

    GetStackBetweenBeginMaximum(old_stack, result, maximum); // Copy Stack from src to dest -> get flipped stack -> call stack->reverse()
    
    old_stack->push(old_head->info_);

    return result;
}
