#include "tests.h"

// ---------------tests-------------

void RunTests() {
    Test1();
    std::cout << "\n\n";
    Test2();
    std::cout << "\n\n";
    Test3();
    std::cout << "\n\n";
    Test4();
    std::cout << "\n\n";
    Test5();
}

void Test1() {
    std::cout << "-------TEST1----\n\n";
    Queue queue;
    queue.view();
    queue.push_back(4);
    queue.push_back(3);
    queue.push_back(2);
    queue.push_front(1);

    std::cout << "1: ";
    queue.view();
    queue.sort();
    std::cout << "2: ";
    queue.view();
    queue.push_front(90);
    queue.push_front(22131);
    queue.push_front(-1);
    std::cout << "3: ";
    queue.view();
    queue.sort();
    std::cout << "4: ";
    queue.view();
    queue.push_back(10000);
    queue.push_front(-2);
    queue.push_back(-3);
    queue.push_front(-5);
    std::cout << "5: ";
    queue.view();
    queue.sort();
    std::cout << "5: ";
    queue.view();
    queue.clear();
}

void Test2() {
    std::cout << "-------TEST2----\n\n";
    Queue queue;
    queue.push_front(3);
    queue.push_front(1);
    queue.push_front(2);

    queue.push_front(3);
    queue.push_front(1);
    queue.push_front(2);

    queue.push_front(3);
    queue.push_front(1);
    queue.push_front(2);

    std::cout << "(After push_front) ";
    queue.view();
    queue.sort();

    std::cout << "(BefPop &ASor) ";
    queue.view();
    queue.pop_front();

    std::cout << "(AftPop queue) ";
    queue.view();

    queue.clear();
    queue.view();
}

void Test3() {
    std::cout << "-------TEST3----\t(Random elements)\n\n";
    Queue queue;
    srand(time(0));
    int n = 10;

    while (n--) {
        int tmp = 0;
        tmp = rand() % 10 + 1;
        queue.push_front(tmp);
    }
    queue.view();
    try {
        queue.pop(FindMax(queue));
    }
    catch (std::runtime_error& e) {
        std::cout << e.what() << '\n';
    }
    queue.view();
}

void Test4() {
    std::cout << "-------TEST4----\t(View - Reverse View)\n\n";
    Queue queue;
    Direction dir = Direction::FRONT;

    for (int i = 1; i <= 5; ++i) {
        queue.push_front(i);
    }

    std::cout << "1: ";
    queue.view(dir);
    std::cout << "2: ";
    SwapViewDirection(dir);
    queue.view(dir);
    SwapViewDirection(dir);

    queue.pop_front();
    std::cout << "3: ";
    queue.view(dir);

    queue.pop_back();
    std::cout << "4: ";
    queue.view(dir);

    queue.pop_back();
    std::cout << "5: ";
    queue.view(dir);

    for (int i = 5; i <= 10; ++i) {
        queue.push_back(i);
    }
    std::cout << "9: ";
    queue.view();
    std::cout << "10: ";
    SwapViewDirection(dir);
    queue.view(dir);
    SwapViewDirection(dir);

    try {
        queue.pop(FindMax(queue));
    }
    catch (std::runtime_error& e) {
        std::cout << e.what() << '\n';
    }
    queue.clear();
}

void Test5() {
    std::cout << "-------TEST5----\t(Delete elemnts)\n\n";
    Queue queue;
    {
        int numbers[] = { 3, 3, 3, 3, 3 };
        for (int i = 0; i < 5; ++i) {
            queue.push_back(numbers[i]);
        }

        std::cout << "1: ";
        queue.view();

        queue.pop(3);

        std::cout << "2: ";
        queue.view();

        queue.clear();
    }

    {
        int numbers[] = { 3, 1, 3, 1, 3, 1, 3};
        for (int i = 0; i < 7; ++i) {
            queue.push_back(numbers[i]);
        }

        std::cout << "3: ";
        queue.view();

        queue.pop(3);

        std::cout << "4: ";
        queue.view();
        queue.clear();
    }
}
