#include "bus_service.h"

BusFlight CreateBusFlight() {	// TODO
	BusFlight tmp_bus_flight;
	tmp_bus_flight.bus_number_ = InputBusNumber();
	InputDestination(tmp_bus_flight.destination_);
	InputDeparture(tmp_bus_flight.departure_time_);
	InputArrival(tmp_bus_flight.arrival_time_);
	return tmp_bus_flight;
}

void ShowBusFlight(const BusFlight& bus_flight) {
	const int& width_number = 10;
	const int& width_word = 10;
	const int& width_time = 6;
	const char kSeparator[] = " | ";
	std::cout << std::fixed << std::left
		<< std::setw(width_number) << bus_flight.bus_number_ << kSeparator
		<< std::setw(width_word) << bus_flight.destination_ << kSeparator
		<< std::setw(width_time) << bus_flight.departure_time_ << kSeparator
		<< std::setw(width_time) << bus_flight.arrival_time_ << kSeparator << '\n';
}

void ShowAllBusFlights(BusFlight*& arr_flight, const int& numbers_of_records) {
	for (int i = 0; i < numbers_of_records; ++i) {
		std::cout << '#' << i + 1 << " | ";
		ShowBusFlight(arr_flight[i]);
	}
}

bool operator<= (const BusFlight& lhs, const BusFlight& rhs) {
	return lhs.arrival_time_ <= rhs.arrival_time_;
}

bool operator< (const BusFlight& lhs, const BusFlight& rhs) {
	return lhs.arrival_time_ < rhs.arrival_time_;
}