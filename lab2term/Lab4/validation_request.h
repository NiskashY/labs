#pragma once

#include <iostream>
#include <string>

#include "stack.h"
#include "rpn.h"

#define CLEAR_LINE() (std::cout << "\033[2K")
#define GO_UP_LINE() (std::cout << "\033[1A")

void Clear(const int& errors = 1);
bool isRequestCorrect(mtl::string&);
bool isOperation(char i);