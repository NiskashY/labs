#pragma once
#include <iomanip>
#include "queue.h"

void ShowMenuHeader(Queue&, const Direction&);

void Push(Queue&, int);

bool Pop(Queue&);

void (Queue::* Operation(Direction& direction))(const int&);

void AddElements(Queue&, Direction&);

int CheckNum();

bool isNCorrect(int& n);
