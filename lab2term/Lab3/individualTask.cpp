#include "individualTask.h"

int FindMax(const Queue& queue) {
    if (queue.empty()) {
        throw std::runtime_error("Pop/FindMax: queue is empty!\n");
    }

    Node* stack_head = queue.GetHead();
    Node* max_node = stack_head;

    while (stack_head) {
        if (stack_head->info_ > max_node->info_) {
            max_node = stack_head;
        }
        stack_head = stack_head->next;
    }

    return max_node->info_;
}