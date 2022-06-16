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

class BusViewer {
private: 
	int amount_of_viewed_flights = 0;
	const char* kEmpty = "Nothing to show!";
	const size_t& width = 14;
	const char* kSeparator = " | ";

public:
	void ShowViewHeader();

	void ShowDelimLine();

	BusViewer() {
		ShowViewHeader();
	}

	~BusViewer() {
		if (amount_of_viewed_flights == 0) {
			std::cout << std::setw(3 * width +3) << std::right << kEmpty << '\n';
		}
		ShowDelimLine();
	}

	void ShowBusFlight(const BusFlight&, const int& i = 0);

	void ShowAllBusFlights(BusFlight*&, const int&, int left = 0);

};

BusFlight CreateBusFlight();

bool operator<= (const BusFlight&, const BusFlight&);

bool operator<= (const BusFlight&, const int&);

bool operator< (const BusFlight&, const BusFlight&);

bool operator< (const BusFlight&, const int&);
