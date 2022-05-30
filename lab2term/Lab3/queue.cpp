#include "queue.h"

#pragma region NodeSection
void SwapViewDirection(Direction& view_direction) {
    if (view_direction == Direction::FRONT) {
        view_direction = Direction::BACK;
    }
    else {
        view_direction = Direction::FRONT;
    }
}


Node* Node::GetDestinationNode(const Direction& direction) {
    if (direction == Direction::BACK) {
        return prev;
    }
    return next;
}

void ConnectNextPrevNodes(Node*& node_pointer) { // connect next and prev nodes
    Node* next_node = node_pointer->next;
    node_pointer = node_pointer->prev;
    node_pointer->next = next_node;
    next_node->prev = node_pointer;
}
#pragma endregion

#pragma region queueSection

void Queue::push_front(const int& info) {
    Node* new_node = new Node(info);
    if (head) {             // if there is at least one item in the queue
        head->prev = new_node;
    }
    new_node->next = head;
    head = new_node;
    if (tail == nullptr) {  // if no elements in queue
        tail = head;
    }
}

void Queue::push_back(const int& info) {
    Node* new_node = new Node(info);
    if (tail) {             // if there is at least one item in the queue
        tail->next = new_node;
    }
    new_node->prev = tail;
    tail = new_node;
    if (empty()) {  // if no elements in queue
        head = tail;
    }
}

void Queue::pop_front(bool isNeedToPrintMessage) {
    if (head) {
        Node* old_node = head;
        head = head->next;
        delete old_node;
        old_node = nullptr;

        if (head == nullptr) { // if we delete head -> in tail garbage -> we need to assign tail to nullptr
            tail = nullptr;
        }
        else { // if at leas one node exist 
            head->prev = nullptr;
        }

        if (isNeedToPrintMessage)
            std::cout << "Delete first element: Done!\n";
    }
    else if (isNeedToPrintMessage) {
        std::cout << "Delete first element: queue is empty!\n";
    }
}

void Queue::pop_back(bool isNeedToPrintMessage) {
    if (head) {
        Node* old_node = tail;
        tail = tail->prev;
        delete old_node;
        old_node = nullptr;

        if (tail == nullptr) { // if we delete tail -> in head garbage -> we need to assign head to nullptr
            head = nullptr;
        }
        else {  // if at leas one node exist 
            tail->next = nullptr;
        }

        if (isNeedToPrintMessage)
            std::cout << "Delete last element: Done!\n";
    }
    else if (isNeedToPrintMessage) {
        std::cout << "Delete last element: queue is empty!\n";
    }
}

void Queue::pop(const int& element, bool isNeedToPrintMessage) {
    if (head) {
        bool isPopSomeElement = false;
        // я конечно был на лекциях, но я хочу удалять все случаи совпадения, а не только 1-ый.
        Node* node_pointer = head->next;

        while (node_pointer->next) { 
            if (node_pointer->info_ == element) {
                Node* current_node = node_pointer;
                ConnectNextPrevNodes(node_pointer); // connect next and prev nodes
                delete current_node;
                current_node = nullptr;
                isPopSomeElement = true;
            }
            node_pointer = node_pointer->next;
        }
       
       if (head->info_ == element) {
           pop_front(false);
           isPopSomeElement = true;
       }
       
       if (tail->info_ == element) {
           pop_back(false);
           isPopSomeElement = true;
       }
       
       if (!isPopSomeElement) {
           std::cout << "No such element in queue\n";
       }
       else if (isNeedToPrintMessage) {
           std::cout << "Delete element " << element << ": Done!\n";
       }
    }
    else if (isNeedToPrintMessage) {
        std::cout << "Delete element: queue is empty!\n";
    }
}

void Queue::view(const Direction& view_direction) {
    Node* node_pointer = (view_direction == Direction::FRONT ? head : tail); // set the beginning from which we want to look
    
    ShowViewHeader(view_direction, node_pointer);

    bool first = true;
    while (node_pointer != nullptr) {
        if (!first) {
            std::cout << ", ";
        }
        first = false;
        std::cout << node_pointer->info_;
        node_pointer = node_pointer->GetDestinationNode(view_direction); // get next or prev node (depends from paramentr direction).
    }
    std::cout << "\n";
}

void Queue::peek() {
    if (tail) {
        std::cout << tail->info_ << std::endl;
    }
    else {
        std::cout << "Peek: Queue is empty!\n";
    }
}

void Queue::clear(bool isNeedToPrintMessage) {
    if (isNeedToPrintMessage && empty()) {
        std::cout << "Nothing to clear!\n";
    }
    else if (head) {
        while (head) {
            Node* old_node = head;
            head = head->next;
            delete old_node;
            old_node = nullptr;
        }
        tail = head = nullptr;  // after delete in tail we have garbage -> we need to assign to nullptr.
        if (isNeedToPrintMessage) {
            std::cout << "Clear: now queue is empty!\n";
        }
    }
}

void Queue::sort() {
    Node* limit = nullptr, * tmp, * t = head;

    if (head == nullptr || head->next == nullptr) {
        std::cout << "Sort: queue is empty or queue has only one element!\n";
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

bool Queue::empty() const {
    return head == nullptr;
}

void ShowViewHeader(const Direction& view_direction, const Node* const node_pointer) {   // Show some text before view of queue
    const char* const kViewDir = (view_direction == Direction::FRONT ? "(Forward)" : "(Reverse)");
    const char* const kQueueView = "Queue view: ";
    const char* const kEmpty = "nothing to show :(";
    std::cout << kViewDir << ' ' << kQueueView;
    if (!node_pointer) {
        std::cout << kEmpty;
    }
}

#pragma endregion
