#pragma once

#include "stack.h"
#include <iostream>

bool isMaximumBeginInvalid(Stack* (&stack), Stack* (&max));
Stack* FindMax(Stack** copy);
void NewReverseStack(Stack*&, Stack*&, Stack*);
Stack* MoveElementsFromTo(Stack* (&old_), Stack* maximum);
