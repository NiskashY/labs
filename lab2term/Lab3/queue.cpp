#include "queue.h"

void Queue::push_front(int info) {
    Queue* tmp = new Queue(info);
    // Добавляю во временную переменную следующий элемент стэка, а затем делаю действия уже с основным стэком
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
    // Добавляю во временную переменную следующий элемент стэка, а затем делаю действия уже с основным стэком
    if (end == nullptr) {
        tmp->next = begin;
        tmp->prev = nullptr;
        tmp->begin = new Queue();

        begin = end = tmp;
    }
    else {
        tmp->next = nullptr;
        tmp->prev = end;
        tmp->begin = new Queue();
        
        
        // это в том случае, если в queue только один элемент -> инициализируем next значением tmp
        // если next != nullptr -> оно инициализируется в части end->next ... т.к. там УЖЕ есть связь между элементами
        if (next == nullptr)
            next = tmp;

        // присваивает end->next = tpm, чтобы не нарушить порядок, 
        // а затем у end'a устанавливаем настоящий конец        
        end->next = tmp;
        end = end->next;
    }
}

void Queue::pop_front(bool isNeedToPrintMessage) {
    if (begin != nullptr) {
        Queue* tmp1 = begin;
        Queue* tmp2 = next;

        begin = next;

        if (next != nullptr) {
            info_ = next->info_;
            next = next->next;
            begin->prev = nullptr;
        }

        delete tmp1, tmp2;
        tmp1 = tmp2 = nullptr;

        if (begin == nullptr)
            end = nullptr;

        if (isNeedToPrintMessage)
            std::cout << "Delete first element: Done!\n";
    }
    else if (isNeedToPrintMessage) {
        std::cout << "Delete first element: queue is empty!\n";
    }
}

void Queue::pop_back(bool isNeedToPrintMessage) {
    if (begin != nullptr) {
        Queue* tmp1 = end;

        end = end->prev;
        end->end = end;
        
        // какой-то дерьмо, почему не работает если я присваива.т одресу в end->next = nullptr
        // оно не меняется и в next, если они совпадают :/

        // тут явно проблема.
        if (end->next == next) {
            next = nullptr;
        }

        end->next = nullptr;


        if (isNeedToPrintMessage)
            std::cout << "Delete last element: Done!\n";
    }
    else if (isNeedToPrintMessage) {
        std::cout << "Delete last element: queue is empty!\n";
    }
}

void Queue::pop(int element, bool isNeedToPrintMessage) {
    if (begin != nullptr) {

        // в GetBegin() ошибка посмотреть почему + скорее всего алгоритм работает не правильно + 
        // проверить как работает этот алгоритм с случаем при удаленни последнего или первого
        // я конечно был на лекциях, но я хочу удалять все случаи совпадения, а не только 1-ый.
        
        Queue* tmp = next;
        
        do {
            if (tmp->info_ == element) {
                Queue* next_tmp = tmp->next;
                Queue* prev_tmp = tmp->prev;
                Queue* del_tmp = tmp;

                tmp = prev_tmp;
                tmp->next = next_tmp;
                next_tmp->prev = tmp;
                next = tmp->next; // делаю для того, чтобы в this у next != непонятно чему. 
                                  // У begin - ok, а у next без этого не ок, т.к. связь для next не устанавливаб вот сложно объяснил но да ладно

                delete del_tmp;
            }
            tmp = tmp->next;
       } while (tmp->next != nullptr);



       if (end->info_ == element) {
           pop_back(false);
       }

       if (begin->info_ == element) {
           pop_front(false);
       }
       
       if (isNeedToPrintMessage)
            std::cout << "Delete element: Done!\n";
    }
    else if (isNeedToPrintMessage) {
        std::cout << "Delete element: queue is empty!\n";
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

void Queue::reverse_view() {
    Queue* tmp = end;
    bool first = true;

    std::cout << "Queue reverse view: ";

    if (tmp == nullptr) {
        std::cout << "nothing to show :(";
    }

    while (tmp != nullptr) {
        if (!first) {
            std::cout << ", ";
        }
        first = false;
        std::cout << tmp->info_;
        tmp = tmp->prev;
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

    // this != nullptr - плохо
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
        end = nullptr;
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