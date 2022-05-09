#pragma once
#include <iostream>
#include <istream>

template <class T>
void CheckNum(std::istream& in, T& var) {
    while (!(in >> var) || in.get() != '\n') {
        std::cout << "Error! Something go wrong ReEnter: ";
        in.clear();
        while (in.get() != '\n');
    }
}
