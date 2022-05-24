#pragma once
#include <iostream>
#include <iomanip>
#include "validation.h"

struct BusFlight {
	int bus_number_ = 0;
	char destination_[10] = "";
	int departure_time_ = 0;
	int arrival_time_ = 0;
};

BusFlight CreateBusFlight();

void LinearSearch(const int& key);

void ShowBusFlight(const BusFlight&);

void ShowAllBusFlights(BusFlight*&, const int&);

bool operator<= (const BusFlight&, const BusFlight&);

bool operator< (const BusFlight&, const BusFlight&);
