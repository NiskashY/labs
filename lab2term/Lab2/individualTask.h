#pragma once

#include "stack.h"
#include <iostream>

bool isMaximumBeginInvalid(const Node* const&, const Node* const&);
Node* FindMax(Stack*&);
void GetStackBetweenBeginMaximum(Stack*&, Stack*&, const Node* const&);
Stack* MoveElementsFromTo(Stack*&, const Node* const&);
