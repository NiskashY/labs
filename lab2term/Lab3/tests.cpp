#include "tests.h"

// ---------------tests-------------

void Test1() {
    std::cout << "-------TEST1----\n\n";

    Queue* queue = new Queue();
    queue->view();


    queue->push_back(4);
    queue->push_back(3);
    queue->push_back(2);
    queue->push_front(1);

    std::cout << "1: ";
    queue->view();

    queue->Sort();
    std::cout << "2: ";
    queue->view();

    queue->push_front(90);
    queue->push_front(22131);
    queue->push_front(-1);

    std::cout << "3: ";
    queue->view();

    queue->Sort();
    std::cout << "4: ";
    queue->view();

    queue->push_back(10000);
    queue->push_front(-2);
    queue->push_back(-3);
    queue->push_front(-5);

    std::cout << "5: ";
    queue->view();

    queue->Sort();
    std::cout << "5: ";
    queue->view();

    delete queue;
}

void Test2() {
    std::cout << "-------TEST2----\n\n";
    Queue* queue = new Queue();


    queue->push_front(3);
    queue->push_front(1);
    queue->push_front(2);

    queue->push_front(3);
    queue->push_front(1);
    queue->push_front(2);

    queue->push_front(3);
    queue->push_front(1);
    queue->push_front(2);

    //    queue->push_front(3);
    //    queue->push_front(1);
    //    queue->push_front(2);
    //    queue->push_front(3);
    //    queue->push_front(1);
    //    queue->push_front(2);
    //    queue->push_front(3);
    //    queue->push_front(1);
    //    queue->push_front(2);
    std::cout << "(After push_front) ";
    queue->view();


    queue->Sort();

    std::cout << "(BefPop &ASor) ";
    queue->view();

    queue->pop_front();
    std::cout << "(AftPop queue) ";
    queue->view();



    queue->clear();
    queue->view();

    delete queue;

}

void Test3() {
    std::cout << "-------TEST3----\t(Random elements)\n\n";
    Queue* queue = new Queue;
    srand(time(0));
    int n = 10;

    while (n--) {
        int tmp = 0;
        tmp = rand() % 10 + 1;
        queue->push_front(tmp);
    }

    queue->view();
    std::cout << "\n";

    // Create new queue from elements between BEGIN and MAX

    delete queue;
}

void Test4() {
    std::cout << "-------TEST4----\t(View - Reverse View)\n\n";
    Queue* queue = new Queue;
    for (int i = 1; i <= 5; ++i) {
        queue->push_front(i);
    }

    std::cout << "1: ";
    queue->view();
    std::cout << "2: ";
    queue->reverse_view();



    queue->pop_front();
    std::cout << "3: ";
    queue->view();
    std::cout << "4: ";
    queue->reverse_view();


    queue->pop_back();
    std::cout << "5: ";
    queue->view();
    std::cout << "6: ";
    queue->reverse_view();

    queue->pop_back();
    std::cout << "7: ";
    queue->view();
    std::cout << "8: ";
    queue->reverse_view();

    for (int i = 5; i <= 10; ++i) {
        queue->push_back(i);
    }
    std::cout << "9: ";
    queue->view();
    std::cout << "10: ";
    queue->reverse_view();


    delete queue;
}

void Test5() {
    std::cout << "-------TEST5----\t(Delete elemnts)\n\n";
    Queue* queue = new Queue();
    {
        int numbers[] = { 3, 3, 3, 3, 3 };
        for (int i = 0; i < 5; ++i) {
            queue->push_back(numbers[i]);
        }

        std::cout << "1: ";
        queue->view();

        queue->pop(3);

        std::cout << "2: ";
        queue->view();

        queue->clear();
    }

    {
        // не проходит тест. Ошбика в pop_back.
        int numbers[] = { 3, 1, 3, 1, 3, 1, 3};
        for (int i = 0; i < 7; ++i) {
            queue->push_back(numbers[i]);
        }

        std::cout << "3: ";
        queue->view();

        queue->pop(3);

        std::cout << "4: ";
        queue->view();

        delete queue;
    }
}