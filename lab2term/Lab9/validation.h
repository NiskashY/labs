#pragma once
#include <iostream>

template <class T>
void CheckNum(T& var) {
    while (!(std::cin >> var) || std::cin.get() != '\n') {
        std::cout << "Error! Something go wrong ReEnter: ";
        std::cin.clear();
        while (std::cin.get() != '\n');
    }
}

int InputBusNumber();

void InputDestination(char*); // return reference in order to not call copy-constructor

void InputDeparture(int&);

void InputArrival(int&);

int InputPosition();
