#include "validation.h"

// TODO: improve validation

int InputBusNumber() {
	const char kInputBusNumber[] = "Input Bus Number ( > 0 ): ";
	int bus_number = 0;

	do {
		std::cout << kInputBusNumber;
		CheckNum(bus_number);
	} while (bus_number <= 0);

	return bus_number;
}

void InputDestination(char* destination) { // return reference in order to not call copy-constructor
	const char kInputDestination[] = "Input Destination: ";
	std::cout << kInputDestination;
	std::cin >> destination;
}

void InputDeparture(int& departure_time) { // return reference in order to not call copy-constructor
	const char kInputDeparture[] = "Input Departure Time: ";
	std::cout << kInputDeparture;
	std::cin >> departure_time;
}

void InputArrival(int& arrival_time) { // return reference in order to not call copy-constructor
	const char kInputArrival[] = "Input Arrival Time: ";
	std::cout << kInputArrival;
	std::cin >> arrival_time;
}
